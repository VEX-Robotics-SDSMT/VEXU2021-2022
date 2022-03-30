#ifndef _GLOBALS_H
#define _GLOBALS_H

#include "generics/drive.h"
#include "robot-config.h"
#include <algorithm>
#include <string>

#define DEBOUNCE_DELAY 200
#define KILL_BUTTON E_CONTROLLER_DIGITAL_DOWN

//const doubles
extern const double FRONT_MOGO_LIFT_UP;
extern const double FRONT_MOGO_LIFT_DOWN;
extern const double FRONT_MOGO_LIFT_RING;
extern const double POT_ADD;
extern const double POT_MULT; 
extern const double BACK_MOGO_ARM_UP;
extern const double BACK_MOGO_ARM_DOWN;
extern const double BACK_MOGO_ARM_RELEASE;
extern const double DIST_MULT;

//drive base class
extern MinesMotorGroup *leftDriveMotors;
extern MinesMotorGroup *rightDriveMotors;
extern FourWheelDrive *driveBase;

extern MinesMotorGroup *frontMogoLift;

//pros declarations
extern  std::uint32_t now;

//globals
extern const int loopDelay;
#endif
