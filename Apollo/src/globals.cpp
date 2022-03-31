#include "globals.h"

//const doubles
const double FRONT_SIXBAR_LIFT_UP = 400;
const double FRONT_SIXBAR_LIFT_DOWN = 30;
const double BACK_MOGO_LIFT_DOWN = -375;// -450
const double BACK_MOGO_LIFT_UP = -240;
const double FRONT_MOGO_LIFT_OUT = 440;
const double FRONT_MOGO_LIFT_IN = 5;
const double CHAIN_LIFT_IN = 0;
const double CHAIN_LIFT_OUT = 120;

const double POT_MULT = 0.5;
const double POT_ADD = -360;

//all const positions are of the form {sixBar, fourBar, chainDelay}
//plunger positions
const double PLUNGE_HOME[3] = {0, 30, -1};
const double PLUNGE_OPEN[3] = {430, 30, 200};
const double PLUNGE_REST[3] = {90, 120, -100};
const double PLUNGE_PREP[3] = {150, 130, -1};
const double PLUNGE_PLUNGE[3] = {90, 210, -1};
const double PLUNGE_SCORE[3] ={400, 5, 600};

//globals
const int loopDelay = 20;
  
MinesMotorGroup *leftDriveMotors = nullptr;
MinesMotorGroup *rightDriveMotors = nullptr;
FourWheelDrive *driveBase = nullptr;

MinesMotorGroup *sixBarLift = nullptr;
MinesMotorGroup *chainLift = nullptr;
MinesMotorGroup *frontMogoLift = nullptr;

