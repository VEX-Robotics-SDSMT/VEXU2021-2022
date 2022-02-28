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
  tailMotor.setStopping(brakeType::hold);
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
  bool skills = false;
  //commented out for scrim until it has been tuned
  
  MinesMotorGroup l(leftDrive1, leftDrive2, leftDrive3, leftDrive4);
  MinesMotorGroup r(rightDrive1, rightDrive2, rightDrive3, rightDrive4);
  MinesMotorGroup lift(leftLiftMotor, rightLiftMotor);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setAllBrakeMode(vex::brakeType::brake);
  d.setTurnPIDConst(0.01, 0, 0);
  d.setDrivePIDConst(.8, 0, 0);
  lift.setStopping(brakeType::hold);


  if (skills)
  {
    //These are all the right motions for skills, but its completly untuned
    toggleFrontMogoLift(lift);
    d.driveTilesPID(.25);
    toggleFrontMogoLift(lift);
    d.turnDegreesAbsolutePID(-48);
    toggleFrontMogoLift(lift);
    d.driveTilesPID(1.4);
    toggleFrontMogoLift(lift);
    d.driveTilesPID(-.75);
    toggleFrontMogoLift(lift);
    d.turnDegreesAbsolutePID(20);
    d.driveTilesPID(.55);
    toggleFrontMogoLift(lift);
    d.driveTilesPID(1.5);
    d.turnDegreesAbsolutePID(-90);
  }
  else
  {
    d.setMotorsRelative(-800, 100);   
    toggleBackMogoArm(false);
    d.setMotorsRelative(600, 100);
    toggleBackMogoArm();
    d.setMotorsRelative(100, 100);
    d.turnDegreesPID(180);
    tailMotor.spinToPosition(0, rotationUnits::deg);
    // toggleFrontMogoLift(lift);
    // d.driveTilesPID(.5, 75);
    // toggleFrontMogoLift(lift);
  }
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
  bool buttonUpDebounce = false;

  Master.ButtonR1.pressed(toggleBackMogoArm);

  //TODO - move to a different function
  MinesMotorGroup l(leftDrive1, leftDrive2, leftDrive3, leftDrive4);
  MinesMotorGroup r(rightDrive1, rightDrive2, rightDrive3, rightDrive4);
  MinesMotorGroup lift(leftLiftMotor, rightLiftMotor);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setDrivePIDConst(6.4, 0, 0.0024);
  d.setTurnPIDConst(0.0064, 0, 0.0002);

  d.setAllBrakeMode(brakeType::brake);
  lift.setStopping(brakeType::hold);

  // User control code here, inside the loop
  while (1) {
    d.arcadeLoopCall(Master.Axis3.position(), Master.Axis1.position());

    if (Master.ButtonL1.pressing())
    {
      lift.spin(directionType::fwd,100, percentUnits::pct);

    }
    else if (Master.ButtonL2.pressing())
    {
      lift.spin(directionType::rev,100, percentUnits::pct);
    }
    else 
    {
      lift.stop();
    }

    //for testing purposes only
    if (pressButton(Master.ButtonUp.pressing(), buttonUpDebounce))
    {
      toggleFrontMogoLift(lift);
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

