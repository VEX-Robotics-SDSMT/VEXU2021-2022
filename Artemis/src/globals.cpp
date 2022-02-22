#include "globals.h"

//const doubles
const double FRONT_MOGO_LIFT_UP = 430;
const double FRONT_MOGO_LIFT_DOWN = 5;
const double BACK_MOGO_ARM_UP = -85;
const double BACK_MOGO_ARM_DOWN = -280;

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *frontMogoLift = nullptr;

