#include "globals.h"

const double PLUNGE_HOME[3] = {15, 0, 0};
const double PLUNGE_OPEN[3] = {400, 0, 300};
const double PLUNGE_REST[3] = {95, 120, -150};
const double PLUNGE_PREP[3] = {130, 170, -150};
const double PLUNGE_PLUNGE[3] = {95, 225, 0};
const double PLUNGE_SCORE[3] ={350, 18, 300};

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *sixBarLift = nullptr;
MinesMotorGroup *chainLift = nullptr;
MinesMotorGroup *frontMogoLift = nullptr;

