/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "globals.h"
#include "generics/helperFunctions.h"
#include "botFunctions.h"
using namespace vex;




// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  //technically can cause a memory leak, but since we'll turn the robot off every time, I'm not worried
  leftDriveMotors = new MinesMotorGroup(leftDriveTop, leftDriveMid, leftDriveBottom);
  rightDriveMotors = new MinesMotorGroup(rightDriveTop, rightDriveMid, rightDriveBottom);
  //driveBase = new FourWheelDrive(leftDriveMotors, rightDriveMotors, &Inertial, &Master);

  sixBarLift = new MinesMotorGroup(right6Bar, left6Bar);
  chainLift = new MinesMotorGroup(rightChainBar, leftChainBar);
  frontMogoLift = new MinesMotorGroup(rightFrontMogoLift, leftFrontMogoLift);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  startUp();

  Master.ButtonR1.pressed(toggleFrontMogoLift);
  Master.ButtonR2.pressed(toggleBackMogoLift);
  //Master.ButtonL1.pressed(toggleSixBarLift);
  //Master.ButtonL2.pressed(toggleChainLift);
  //Master.ButtonA.pressed(togglePlunger);

  //TODO - move to a different function
  MinesMotorGroup l(leftDriveTop, leftDriveMid, leftDriveBottom);
  MinesMotorGroup r(rightDriveTop, rightDriveMid, rightDriveBottom);
  FourWheelDrive d(&l, &r, &Inertial, &Master);


  // User control code here, inside the loop
  while (1) {
    d.arcadeLoopCall(Master.Axis3.position(), -Master.Axis1.position());

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

