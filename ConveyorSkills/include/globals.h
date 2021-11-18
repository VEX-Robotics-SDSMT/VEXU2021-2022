#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "../src/generics/straightDriveBase/drive.h"
#include "vex.h"

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

#define TALL_LIFT_SPEED 75
#define SHORT_LIFT_SPEED 75
#define INTAKE_SPEED 100

//drive base class
extern MinesMotorGroup *rightDriveMotors;
extern MinesMotorGroup *leftDriveMotors;
extern FourWheelDrive* driveBase;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;

#endif
