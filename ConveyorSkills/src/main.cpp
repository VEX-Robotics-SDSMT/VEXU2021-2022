/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightFront           motor         1               
// rightMid             motor         2               
// rightBack            motor         3               
// leftFront            motor         11              
// leftMid              motor         16              
// leftBack             motor         20              
// Inertial             inertial      6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "../include/globals.h"
#include "generics/helperFunctions.h"
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

  //driveBase = &drive;
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  //this is some of the greasiest code in this entire project
  //if you can find ANY other way to get this to work, PLEASE do it
  MinesMotorGroup left = MinesMotorGroup(leftFront, leftBack);
  leftDriveMotors = &left;
  MinesMotorGroup right = MinesMotorGroup(rightFront, rightBack);
  rightDriveMotors = &right;
  FourWheelDrive drive(leftDriveMotors, rightDriveMotors, &Inertial, &Master);

  MinesMotorGroup tallLift = MinesMotorGroup(leftTallLift, rightTallLift);
  MinesMotorGroup shortLift = MinesMotorGroup(leftShortLift, rightShortLift);

  bool aDebounce = false;
  bool pnumaticToggle = false;

  // User control code here, inside the loop
  while (1) {

    drive.arcadeLoopCall(Master.Axis3.position(), -Master.Axis4.position());

    if(Master.ButtonR1.pressing())
    {
      tallLift.spin(directionType::fwd, TALL_LIFT_SPEED, percentUnits::pct);
    }
    else if (Master.ButtonR2.pressing())
    {
      tallLift.spin(directionType::rev, TALL_LIFT_SPEED, percentUnits::pct);
    }
    else
    {
      tallLift.stop();
    }

    if(Master.ButtonX.pressing())
    {
      shortLift.spin(directionType::fwd, SHORT_LIFT_SPEED, percentUnits::pct);
    }
    else if (Master.ButtonY.pressing())
    {
      shortLift.spin(directionType::rev, SHORT_LIFT_SPEED, percentUnits::pct);
    }
    else
    {
      shortLift.stop();
    }

    if(Master.ButtonL2.pressing())
    {
      intake.spin(directionType::fwd, INTAKE_SPEED, percentUnits::pct);
    }
    else if (Master.ButtonL1.pressing())
    {
      intake.spin(directionType::rev, INTAKE_SPEED, percentUnits::pct);
    }
    else
    {
      intake.stop();
    }


    if (pressButton(Master.ButtonA.pressing(), aDebounce))
    {
      if(pnumaticToggle)
      {
        hook.close();
        pnumaticToggle = false;
      }
      else
      {
        hook.open();
        pnumaticToggle = true;
      }
    }
    

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

