#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "../src/straightDriveBase/drive.h"
#include "MinesMotorGroup.h"
#include "vex.h"

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

//drive base class
extern MinesMotorGroup rightDriveMotors;
extern MinesMotorGroup leftDriveMotors;
extern FourWheelDrive* driveBase;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;

#endif
