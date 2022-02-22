#include "globals.h"

//const doubles
const double FRONT_SIXBAR_LIFT_UP = 400;
const double FRONT_SIXBAR_LIFT_DOWN = 30;
const double BACK_MOGO_LIFT_DOWN = -450;
const double BACK_MOGO_LIFT_UP = -290;
const double FRONT_MOGO_LIFT_OUT = 430;
const double FRONT_MOGO_LIFT_IN = 5;
const double CHAIN_LIFT_IN = 0;
const double CHAIN_LIFT_OUT = 120;

//all const positions are of the form {sixBar, chainBar, chainDelay}
//plunger positions
const double PLUNGE_HOME[3] = {15, 0, 0};
const double PLUNGE_OPEN[3] = {400, 0, 300};
const double PLUNGE_REST[3] = {95, 120, -150};
const double PLUNGE_PREP[3] = {130, 170, -150};
const double PLUNGE_PLUNGE[3] = {100, 230, 0};
const double PLUNGE_SCORE[3] ={355, 18, 300};

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *sixBarLift = nullptr;
MinesMotorGroup *chainLift = nullptr;
MinesMotorGroup *frontMogoLift = nullptr;

