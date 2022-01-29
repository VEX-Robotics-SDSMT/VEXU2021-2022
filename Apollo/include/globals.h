#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "generics/drive.h"
#include "vex.h"

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

//bot-specific constants
#define FRONT_SIXBAR_LIFT_UP 70
#define FRONT_SIXBAR_LIFT_DOWN 30
#define BACK_MOGO_LIFT_DOWN -90
#define BACK_MOGO_LIFT_UP -30
#define FRONT_MOGO_LIFT_OUT 120
#define FRONT_MOGO_LIFT_IN 0
#define CHAIN_LIFT_IN 0
#define CHAIN_LIFT_OUT 120

//drive base class
extern MinesMotorGroup rightDriveMotors;
extern MinesMotorGroup leftDriveMotors;
extern FourWheelDrive drive;

extern MinesMotorGroup sixBarLift;
extern MinesMotorGroup chainLift;
extern MinesMotorGroup frontMogoLift;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;

#endif
