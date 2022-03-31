#include "../../include/generics/drive.h"


// Prevents inifinite rotation and bounding into 360 degrees
float FourWheelDrive::degreeBoundingHelper(float inDegrees)
{
  float inRadians = degreesToRadians(inDegrees);
  return radiansToDegrees(atan2(sin( inRadians), cos(inRadians)));
}

float FourWheelDrive::degreesToRadians(float radians)
{
  return radians * M_PI / 180.0;
}

float FourWheelDrive::radiansToDegrees(float degrees)
{
  return degrees * 180.0 / M_PI;
}

float FourWheelDrive::bindToMagnitude(float value, float MAX_MAGNITUDE)
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

void FourWheelDrive::setAllBrakeMode(brakeType mode)
{
  rightMotors->setStopping(mode);
  leftMotors->setStopping(mode);
}

void FourWheelDrive::setMotorPercents(int leftSpeed, int rightSpeed)
{
    //if one side of the drive is being told to go faster than 100, this makes sure it can't
  if (abs(leftSpeed) > 100)
  {
    leftSpeed = leftSpeed * (100.0 / abs(leftSpeed));
    rightSpeed = rightSpeed * (100.0 / abs(leftSpeed));
  }
  if(abs(rightSpeed) > 100)
  {
    rightSpeed = rightSpeed * (100.0 / abs(rightSpeed));
    leftSpeed = leftSpeed * (100.0/ abs(rightSpeed));
  }

  leftMotors->spin(directionType::fwd, leftSpeed, percentUnits::pct);
  rightMotors->spin(directionType::fwd, rightSpeed, percentUnits::pct);
}
