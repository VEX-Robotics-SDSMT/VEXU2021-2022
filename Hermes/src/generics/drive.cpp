#include "generics/drive.h"

using namespace std;
using namespace vex;

FourWheelDrive::FourWheelDrive(MinesMotorGroup & left, MinesMotorGroup & right,
    inertial& sensor, controller& masterIn)
{
    MinesMotorGroup *rightPointer = &right;
    MinesMotorGroup *leftPointer = &left;
    inertial *inertialPointer = &sensor;
    controller *controllerPointer = &masterIn;

    rightMotors = rightPointer;
    leftMotors = leftPointer;
    inertialSensor = inertialPointer;
    master = controllerPointer;

    rightMotors->spin(directionType::fwd, 100, percentUnits::pct);

    //setAllBrakeMode(BRAKE_MODE);

    //readCalibration();
}

FourWheelDrive::FourWheelDrive(MinesMotorGroup* left, MinesMotorGroup* right,
    inertial* sensor, controller* masterIn)
{
    rightMotors = right;
    leftMotors = left;
    inertialSensor = sensor;
    master = masterIn;

    setAllBrakeMode(BRAKE_MODE);

    //readCalibration();
}

void FourWheelDrive::setDrivePIDConst(double p, double i, double d)
{
  driveKP = p;
  driveKI = i;
  driveKD = d;
}
void FourWheelDrive::setTurnPIDConst(double p, double i, double d)
{
  turnKP = p;
  turnKI = i;
  driveKD = d;
}

//take in a vector of motors, and set their speed to a value
void FourWheelDrive::setMotors(MinesMotorGroup *motors, double speed)
{
  motors->spin(directionType::fwd, speed, VEL_UNIT);
}

void FourWheelDrive::rawSetMotors(double speed, double bias)
{
    if (bias > 1)
    {
        speed *= (1 / bias);
    }


    setMotors(leftMotors, speed);
    setMotors(rightMotors, speed * bias);
}

void FourWheelDrive::setMotors(double speed)
{
    //speed capping
    if (speed > maxSpeed)
    {
        speed = maxSpeed;
        rawSetMotors(speed, LRBiasHigh);
        //lcd::set_text(0, "speed > maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHigh));
    }
    else if(speed > midSpeed)
    {
        double highPercent = (speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed - speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLow * lowPercent + LRBiasHigh * highPercent);
        //lcd::set_text(0, "speed > midSpeed: " + to_string(speed) + " bias: "
        //        + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else if (speed >= 0)
    {
        rawSetMotors(speed, LRBiasLow);
        //lcd::set_text(0, "speed > 0: " + to_string(speed) + " bias: " + to_string(LRBiasLow));
    }
    //backwards biases
    else if (speed < -maxSpeed)
    {
        speed = -maxSpeed;
        rawSetMotors(speed, LRBiasHighBack);
        //lcd::set_text(0, "speed < -maxSpeed: " + to_string(speed) + " bias: " + to_string(LRBiasHighBack));
    }
    else if (speed < -midSpeed)
    {
        double highPercent = (-speed - midSpeed) / (maxSpeed - midSpeed);
        double lowPercent = (maxSpeed + speed) / (maxSpeed - midSpeed);

        rawSetMotors(speed, LRBiasLowBack * lowPercent + LRBiasHighBack * highPercent);
        //lcd::set_text(0, "speed < -midSpeed: " + to_string(speed) + " bias: "
        //        + to_string(LRBiasLow * lowPercent + LRBiasHigh * highPercent));
    }
    else //if (speed < 0)
    {
        rawSetMotors(speed, LRBiasLowBack);
        //lcd::set_text(0, "speed < 0: " + to_string(speed) + " bias: " + to_string(LRBiasLowBack));
    }
}

//tqke in a vector of motors, and call the move relative function for all of them with a given distance and speed
void FourWheelDrive::setMotorsRelative(MinesMotorGroup * motors, double distance, double speed, bool waitForCompletion)
{
  motors->spinFor(distance, ROT_UNIT, speed, VEL_UNIT, waitForCompletion);
}

void FourWheelDrive::setMotorsRelative(double distance, double speed)
{
  setMotorsRelative(rightMotors, distance, speed, false);
  setMotorsRelative(leftMotors, distance, speed, true);
}

void FourWheelDrive::setZeroPosition()
{
  leftMotors->resetPosition();
  rightMotors->resetPosition();
}

double FourWheelDrive::getPosition(MinesMotorGroup * motors)
{
    return motors->position(ROT_UNIT);
}

double FourWheelDrive::getAllPosition()
{
    return (getPosition(rightMotors) + getPosition(leftMotors)) / 2.0;
}

double FourWheelDrive::getSpeed(MinesMotorGroup * motors)
{
  return motors->velocity(VEL_UNIT);
}

double FourWheelDrive::getAllSpeed()
{
    return (getSpeed(rightMotors) + getSpeed(leftMotors)) / 2.0;
}

//TODO port a version to MinesMotorGroup
void FourWheelDrive::accelerate(double targetSpeed)
{
	const double TOLERANCE = 0.5;

	double currSpeed = getAllSpeed();
	if(currSpeed < targetSpeed)
	{
		while(currSpeed < targetSpeed - TOLERANCE)
		{
			currSpeed += maxAccelerationForward;
			setMotors(currSpeed);
			task::sleep(LOOP_DELAY);
		}
	}
	else
	{
		while(currSpeed > targetSpeed + TOLERANCE)
		{
			currSpeed -= maxAccelerationBackward;
			setMotors(currSpeed);
			task::sleep(LOOP_DELAY);
		}
	}
}

void FourWheelDrive::driveTilesPID(float numTiles, float desiredSpeed)
{
    float INTEGRATOR_MAX_MAGNITUDE = 1000;
    float DELTA_T = LOOP_DELAY / 1000.0;
    const int STOP_LOOPS = 35;
    const float TILE_TOLERANCE = 0.01;
    // 4 Inches wheels, 600RPM motors, measured 222.22 ticks/rotation
    const double TICKS_PER_TILE = 1333.3;
    float currentDistance = 0;

    float porportionalAmount = 0;
    float integralAmount = 0;
    float derivativeAmount = 0;

    long iterations = 1;
    float lastDistance = 0;
    float accumulatedDistance = 0;

    float lastEncoderVal = getAllPosition();
    float runTime = 0;
    int stopLoopCount = 0;

    int maxRunTime = max(ONE_SEC_IN_MS * 5, ONE_SEC_IN_MS * fabs(numTiles) * 2);

    Brain.Screen.print("preLoop");
    while( stopLoopCount <= STOP_LOOPS && runTime < maxRunTime)
    {
        porportionalAmount = numTiles - currentDistance;

        accumulatedDistance += porportionalAmount;
        accumulatedDistance = bindToMagnitude(accumulatedDistance, INTEGRATOR_MAX_MAGNITUDE);

        integralAmount = accumulatedDistance * DELTA_T;

        derivativeAmount = (lastDistance - currentDistance) / DELTA_T;

        float total = porportionalAmount * driveKP + integralAmount * driveKI - derivativeAmount * driveKD;
        total = bindToMagnitude(total, 1);

        float speed = total * desiredSpeed;

        float currentEncoderVal = getAllPosition();

        currentDistance += (currentEncoderVal - lastEncoderVal) / TICKS_PER_TILE;

        setMotors(rightMotors, speed);
        setMotors(leftMotors, speed);

        iterations++;
        lastDistance = porportionalAmount;
        lastEncoderVal = currentEncoderVal;

        runTime += LOOP_DELAY;
        task::sleep(LOOP_DELAY);

        if(fabs(degreeBoundingHelper(currentDistance) - degreeBoundingHelper(numTiles))
                <= TILE_TOLERANCE)
            { stopLoopCount++;}
        else
            {stopLoopCount = 0;}
    }

    setMotors(rightMotors, 0);
    setMotors(leftMotors, 0);
}

void FourWheelDrive::turnDegreesPID(float numDegrees, float desiredSpeed)
{
    float startDegrees = degreeBoundingHelper(inertialSensor->heading());
    turnDegreesAbsolutePID(degreeBoundingHelper(numDegrees + startDegrees), desiredSpeed);
}

void FourWheelDrive::turnDegreesAbsolutePID(float targetDegrees, float desiredSpeed)
{
  //lcd::set_text(1, "target heading: " + to_string(targetDegrees) + " " + to_string(desiredSpeed));

  float INTEGRATOR_MAX_MAGNITUDE = 1000;
  float DELTA_T = LOOP_DELAY / 1000.0;
  const int STOP_LOOPS = 50;
  const float TURN_TOLERANCE = 1;
  const float DESIRED_SPEED = 70;
  const int MAX_RUN_TIME = ONE_SEC_IN_MS * 7.5;
  float endingDegrees = degreeBoundingHelper(targetDegrees);
  float currentDegrees = degreeBoundingHelper(inertialSensor->heading());

  //This is here to keep all of the tuning constants in the same place
  if(desiredSpeed == -1)
  {
      desiredSpeed = DESIRED_SPEED;
  }

  float porportionalAmount = 0;
  float integralAmount = 0;
  float derivativeAmount = 0;
  float accumulatedDegrees = 0;

  float lastDegrees = 0;
  float runTime = 0;
  int stopLoopCount = 0;  

  while( stopLoopCount <= STOP_LOOPS && runTime < MAX_RUN_TIME )
  {
    currentDegrees = degreeBoundingHelper(inertialSensor->heading());

    porportionalAmount = degreeBoundingHelper(endingDegrees - currentDegrees);

    accumulatedDegrees += porportionalAmount;
    accumulatedDegrees = bindToMagnitude(accumulatedDegrees, INTEGRATOR_MAX_MAGNITUDE);

    derivativeAmount = (porportionalAmount - lastDegrees) / DELTA_T;
    lastDegrees = porportionalAmount;

    integralAmount = accumulatedDegrees * DELTA_T;

    float total = porportionalAmount * turnKP + integralAmount * turnKI - derivativeAmount * turnKD;
    total = bindToMagnitude(total, 1);
    float speed = total * desiredSpeed;


    setMotors(rightMotors, -speed);
    setMotors(leftMotors, speed);

    runTime += LOOP_DELAY;
    task::sleep(LOOP_DELAY);

    if(fabs(degreeBoundingHelper(currentDegrees) - degreeBoundingHelper(endingDegrees)) <= TURN_TOLERANCE)
    {
        stopLoopCount++;
    }
    else
    {
        stopLoopCount = 0;
    }
  }

  setMotors(0);
}

//user control functions
void FourWheelDrive::tankLoopCall(double leftSide, double rightSide)
{
  setMotorPercents(leftSide, rightSide);
}

void FourWheelDrive::arcadeLoopCall(double forwardAxis, double turnAxis)
{
  int leftMotorPercent = 0;
  int rightMotorPercent = 0;

  if(fabs(forwardAxis) > driveThreshold || fabs(turnAxis) > turnThreshold)
  {
    leftMotorPercent = forwardAxis;
    rightMotorPercent = forwardAxis;

    if(fabs(turnAxis) > turnThreshold)
    {
      leftMotorPercent += turnAxis;
      rightMotorPercent -= turnAxis;
    }
  }
  else
  {
    leftMotorPercent = 0;
    rightMotorPercent = 0;
  }

  setMotorPercents(leftMotorPercent, rightMotorPercent);
}