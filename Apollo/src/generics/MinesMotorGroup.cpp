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

bool MinesMotorGroup::getTargetReached()
{
  return tolerance > fabs(target - position(ROT_UNITS));
}
bool MinesMotorGroup::getPIDRunning()
{
  return runnningPId;
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
  double error = target - position(ROT_UNITS);

  while (runnningPId)
  {
    PIDOneLoop(error, integral);
    task::sleep(LOOP_DELAY);
  }
}

void MinesMotorGroup::runPIDToPosition()
{
  runnningPId = false;
  double integral = 0;
  double error = target - position(ROT_UNITS);
  double errorCount = 0;
  double t = 0;
  task::sleep(LOOP_DELAY * 1.5);
  runnningPId = true;
  while (errorCount < toleranceTime && t < timeout && runnningPId)
  {
    PIDOneLoop(error, integral);
    t += LOOP_DELAY;
    if (error < tolerance)
    {
      errorCount += LOOP_DELAY;
    }
    else
    {
      errorCount = 0;
    }

    task::sleep(LOOP_DELAY);
  }
}

void MinesMotorGroup::PIDOneLoop(double &lastE, double &lastI)
{
  double error = target - position(ROT_UNITS);
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