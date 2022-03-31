#include "../../include/generics/MinesMotorGroup.h"

MinesMotorGroup::MinesMotorGroup(motor m1, motor m2):motor_group(m1, m2){}
MinesMotorGroup::MinesMotorGroup(motor m1, motor m2, motor m3):motor_group(m1, m2, m3){}
MinesMotorGroup::MinesMotorGroup(motor m1, motor m2, motor m3, motor m4):motor_group(m1, m2, m3, m4){}




void MinesMotorGroup::startPID()
{
  //TODO multithreading tasks
} 
void MinesMotorGroup::stopPID()
{ 
  runnningPId = false;
}

void MinesMotorGroup::setPIDSpeed(double s)
{
  speed = s;
}
void MinesMotorGroup::setPIDValues(double p, double i, double d)
{
  kp = p;
  ki = i;
  kd = d;
}
void MinesMotorGroup::setExternalPositionFunc(double (*func)())
{
  pointerFilled = true;
  externalPositionFunc = func;
}

bool MinesMotorGroup::getTargetReached() 
{
  return tolerance > fabs(target - getPosition());
}
bool MinesMotorGroup::getPIDRunning()
{
  return runnningPId;
}
double MinesMotorGroup::getPosition()
{
  if (!pointerFilled)
  {
    return position(ROT_UNITS);
  }
  else
  {
    return externalPositionFunc();
  }
}

void MinesMotorGroup::startMoveToPosition(double pos, double timeoutVal, double toleranceVal)
{
  target = pos;
  tolerance = toleranceVal;
  timeout = timeoutVal;

  runPIDToPosition(); //TODO needs to be task
}

void MinesMotorGroup::startHoldPosition(double pos)
{
  target = pos;
  runPIDForever(); //TODO needs to be task
}

void MinesMotorGroup::runPIDForever()
{
  double integral = 0;
  double error = target - getPosition();

  while (runnningPId)
  {
    PIDOneLoop(error, integral);
    task::sleep(LOOP_DELAY);
  }

  spin(directionType::fwd, 0, percentUnits::pct);
}

void MinesMotorGroup::runPIDToPosition()
{
  runnningPId = false;
  double integral = 0;
  double error = target - getPosition();
  double errorCount = 0;
  double t = 0;
  task::sleep(LOOP_DELAY * 1.5);
  runnningPId = true;
  //TODO timeout should perhaps be how long without progress
  while (errorCount < toleranceTime && t < timeout && runnningPId)
  {
    PIDOneLoop(error, integral);
    t += LOOP_DELAY;
    if (fabs(error) < tolerance) 
    {
      errorCount += LOOP_DELAY; 
    }
    else
    {
      errorCount = 0;
    } 

    task::sleep(LOOP_DELAY);
  }

  spin(directionType::fwd, 0, percentUnits::pct);
}

void MinesMotorGroup::PIDOneLoop(double &lastE, double &lastI)
{
  double error = target - getPosition();
  double positional = kp * error;
  double integral = ki * ( lastI + (error * LOOP_DELAY));
  double derivative = kd * ((error - lastE) / LOOP_DELAY);

  double controlVariable = positional + integral + derivative;
  controlVariable = bindToMagnitude(controlVariable, 1);
  double modSpeed = controlVariable * speed;
  spin(directionType::fwd, modSpeed, percentUnits::pct);
  lastE = error;
  lastI = integral;
}

double MinesMotorGroup::bindToMagnitude(double value, double MAX_MAGNITUDE)
{
  if(value > MAX_MAGNITUDE)
  {
    value = MAX_MAGNITUDE;
  }
  else if(value < -MAX_MAGNITUDE)
  {
    value = -MAX_MAGNITUDE;
  }
  return value;
}