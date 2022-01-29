#include "globals.h"

//drive base class
MinesMotorGroup leftDriveMotors = MinesMotorGroup(leftDriveTop, leftDriveMid, leftDriveBottom);
MinesMotorGroup rightDriveMotors = MinesMotorGroup(rightDriveTop, rightDriveMid, leftDriveBottom);
FourWheelDrive drive(&leftDriveMotors, &rightDriveMotors, &Inertial, &Master);

MinesMotorGroup sixBarLift = MinesMotorGroup(right6Bar, left6Bar);
MinesMotorGroup chainLift = MinesMotorGroup(rightChainBar, leftChainBar);
MinesMotorGroup frontMogoLift = MinesMotorGroup(rightFrontMogoLift, leftFrontMogoLift);

//globals
const int loopDelay = 20;
