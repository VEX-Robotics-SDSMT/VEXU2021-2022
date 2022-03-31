#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "generics/drive.h"
#include "robot-config.h"

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

//bot-specific constants
extern const double FRONT_SIXBAR_LIFT_UP;
extern const double FRONT_SIXBAR_LIFT_DOWN;
extern const double BACK_MOGO_LIFT_DOWN;
extern const double BACK_MOGO_LIFT_UP;
extern const double FRONT_MOGO_LIFT_OUT;
extern const double FRONT_MOGO_LIFT_IN;
extern const double CHAIN_LIFT_IN;
extern const double CHAIN_LIFT_OUT;

extern const double POT_MULT;
extern const double POT_ADD;


//negative chain delay means chain goes first
extern const double PLUNGE_HOME[3];
extern const double PLUNGE_OPEN[3];
extern const double PLUNGE_REST[3];
extern const double PLUNGE_PREP[3];
extern const double PLUNGE_PLUNGE[3];
extern const double PLUNGE_SCORE[3];


//drive base class
extern MinesMotorGroup *leftDriveMotors;
extern MinesMotorGroup *rightDriveMotors;
extern FourWheelDrive *driveBase;

extern MinesMotorGroup *sixBarLift;
extern MinesMotorGroup *chainLift;
extern MinesMotorGroup *frontMogoLift;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;
#endif
