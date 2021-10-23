#include "globals.h"

//drive base class
FourWheelDrive* driveBase;
MinesMotorGroup leftDriveMotors = MinesMotorGroup(leftFront, leftMid, leftBack);
MinesMotorGroup rightDriveMotors = MinesMotorGroup(rightFront, rightMid, rightBack);

//globals
const int loopDelay = 20;
