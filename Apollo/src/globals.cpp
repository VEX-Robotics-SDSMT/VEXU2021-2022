#include "globals.h"

//const doubles
const double FRONT_SIXBAR_LIFT_UP = 400;
const double FRONT_SIXBAR_LIFT_DOWN = 30;
const double BACK_MOGO_LIFT_DOWN = -441;// -450
const double BACK_MOGO_LIFT_UP = -290;
const double FRONT_MOGO_LIFT_OUT = 430;
const double FRONT_MOGO_LIFT_IN = 5;
const double CHAIN_LIFT_IN = 0;
const double CHAIN_LIFT_OUT = 120;

//all const positions are of the form {sixBar, fourBar, chainDelay}
//plunger positions
const double PLUNGE_HOME[3] = {0, 30, 0};
const double PLUNGE_OPEN[3] = {430, 30, 200};
const double PLUNGE_REST[3] = {90, 120, -100};
const double PLUNGE_PREP[3] = {150, 130, 0};
const double PLUNGE_PLUNGE[3] = {90, 200, 0};
const double PLUNGE_SCORE[3] ={400, 5, 600};

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *sixBarLift = nullptr;
MinesMotorGroup *chainLift = nullptr;
MinesMotorGroup *frontMogoLift = nullptr;

