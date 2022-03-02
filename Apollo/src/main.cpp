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

  sixBarLift->setStopping(brakeType::hold);
  chainLift->setStopping(brakeType::hold);
  frontMogoLift->setStopping(brakeType::hold);
  backMogoArm.setStopping(brakeType::hold);
  backMogoArm.resetPosition();
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
  bool skills = true;
  //commented out for scrim until it has been tuned
  
  MinesMotorGroup l(leftDriveTop, leftDriveMid, leftDriveBottom);
  MinesMotorGroup r(rightDriveTop, rightDriveMid, rightDriveBottom);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setAllBrakeMode(vex::brakeType::brake);
  d.setLRBias(1);
  d.setTurnPIDConst(0.01, 0, 0);
  d.setDrivePIDConst(.8, 0, 0);

  if (skills)
  {
    toggleBackMogoArm(false);
    d.driveTilesPID(-2.9);
    toggleBackMogoArm();
    d.driveTilesPID(-1.75);
    d.turnDegreesAbsolutePID(76);
    movePlungerOpen();
    toggleFrontMogoLift();
    d.driveTilesPID(1.5,30);
    toggleFrontMogoLift();
    movePlungerRest();
    d.driveTilesPID(-1.5,30);
    d.turnDegreesAbsolutePID(-1);
    d.driveTilesPID(3.1);
    d.turnDegreesAbsolutePID(-24);
    toggleBackMogoArm();
    movePlungerOpen();
    d.driveTilesPID(1.2);
    d.turnDegreesAbsolutePID(68);
    d.driveTilesPID(-0.35);
    toggleBackMogoArm();
    d.driveTilesPID(0.3);
    d.turnDegreesAbsolutePID(250);
    //d.driveTilesPID(-0.8);
    toggleBackMogoArm(false);
    plungeUntilTime(1500, 50000);
    movePlungerScore();
    //d.driveTilesPID(0.43);
    //autoBalance(d, 300, 30);

  }
  else
  {
    toggleBackMogoArm(false);
    d.driveTilesPID(-2.98);
    toggleBackMogoArm();
    d.driveTilesPID(1.9);
    d.turnDegreesAbsolutePID(310);
    movePlungerOpen();
    toggleFrontMogoLift();
    d.driveTilesPID(1.6,35);
    toggleFrontMogoLift();
    d.turnDegreesAbsolutePID(32); 
    d.driveTilesPID(.2);
    plungeUntilTime(1500, 43000);
    movePlungerScore();
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
  //do this only once at the beginnning of the each match
  Brain.Timer.reset();

  bool buttonYDebounce = false;
  bool buttonXDebounce = false;

  Master.ButtonR1.pressed(toggleFrontMogoLift);

  Master.ButtonUp.pressed(movePlungerOpen);
  Master.ButtonDown.pressed(movePlungerRest);
  Master.ButtonLeft.pressed(movePlungerPrep);
  Master.ButtonRight.pressed(movePlungerScore);
  Master.ButtonA.pressed(movePlungerPlunge);

  Master.ButtonB.pressed(plungeRing);
  //Master.ButtonX.pressed(togglePlunger);


  //TODO - move to a different function
  MinesMotorGroup l(leftDriveTop, leftDriveMid, leftDriveBottom);
  MinesMotorGroup r(rightDriveTop, rightDriveMid, rightDriveBottom);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setDrivePIDConst(0.8, 0, 0);
  d.setTurnPIDConst(0.01, 0, 0);

  l.setStopping(brakeType::coast);
  r.setStopping(brakeType::coast);

  // User control code here, inside the loop
  while (1) {
    d.arcadeLoopCall(Master.Axis3.position(), Master.Axis4.position());

    if (Master.ButtonL1.pressing() && backMogoArm.position(rotationUnits::deg) < -50.0)
    {
      backMogoArm.spin(directionType::fwd, 100, percentUnits::pct);
    }
    else if (Master.ButtonL2.pressing() && backMogoArm.position(rotationUnits::deg) > -500.0)
    {
      backMogoArm.spin(directionType::rev, 100, percentUnits::pct);
    }
    else 
    {
      backMogoArm.stop();
    }

    //for testing purpouses only 
    /*
    if (pressButton(Master.ButtonX.pressing(), buttonXDebounce))
    {
      autoBalance(d, 800, 20);
    }*/
    /*
    if (pressButton(Master.ButtonY.pressing(), buttonYDebounce))
    {
      d.swingDrivePID(-1, 0);
    }
    */

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

