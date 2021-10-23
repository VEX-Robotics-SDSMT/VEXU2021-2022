#include "DifferentialDrive.h"


// Prevents inifinite rotation and bounding into 360 degrees
float DifferentialDrive::degreeBoundingHelper(float inDegrees)
{
  float inRadians = degreesToRadians(inDegrees);
  return radiansToDegrees(atan2(sin( inRadians), cos(inRadians)));
}

float DifferentialDrive::degreesToRadians(float radians)
{
  return radians * M_PI / 180.0;
}

float DifferentialDrive::radiansToDegrees(float degrees)
{
  return degrees * 180.0 / M_PI;
}

float DifferentialDrive::bindToMagnitude(float value, float MAX_MAGNITUDE)
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

void DifferentialDrive::setAllBrakeMode(std::vector<motor> *motors, brakeType mode)
{
    int size = (int)motors->size();

    for( int i = 0; i < size; i++)
    {
        motors->at(i).setBrake(mode);
    }
}

void DifferentialDrive::setAllBrakeMode(brakeType mode)
{
    setAllBrakeMode(rightMotors, mode);
    setAllBrakeMode(leftMotors, mode);
}
