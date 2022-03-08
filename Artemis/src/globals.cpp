#include "globals.h"

//const doubles
const double FRONT_MOGO_LIFT_UP = -300; //600
const double FRONT_MOGO_LIFT_DOWN = -1550; //1900
const double FRONT_MOGO_LIFT_RING = -700;
const double BACK_MOGO_ARM_UP = -20;
const double BACK_MOGO_ARM_DOWN = -800;
const double BACK_MOGO_ARM_RELEASE = -750;

const double DIST_MULT = 1;

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *frontMogoLift = nullptr;
