/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Mines                                                      */
/*    Created:      3/29/2022                                                 */
/*    Description:  hermes                                                     */
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
  //driveBase.setDrivePIDConst(6.4, 0, 0.0024);
  //driveBase.setTurnPIDConst(0.0064, 0, 0.0002);
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
  bool yNot = true;
  int matchTime = Brain.Timer.time();
  
  MinesMotorGroup rightWheels(rightFront, rightTop, rightBack);
  MinesMotorGroup leftWheels(leftFront, leftTop, leftBack);
  FourWheelDrive driveBase(leftWheels, rightWheels, inertialSensor, master);

  MinesMotorGroup backClamp(leftBackClamp, rightBackClamp);
  MinesMotorGroup lift(leftLift, rightLift);

  driveBase.setAllBrakeMode(brakeType::coast);
  lift.setStopping(brakeType::hold);
  backClamp.setStopping(brakeType::hold);
  liftClamp.setStopping(brakeType::hold);
  driveBase.setTurnPIDConst(0.0092, 0.0001, 0.01);
  driveBase.setDrivePIDConst(4, 0.01, 0.0003);

  if (yNot)
  {
    //get middle
    backClamp.spinToPosition(30, degrees, false);
    liftClamp.spinToPosition(FRONT_CLAMP_UP, degrees, false);
    driveBase.driveTilesPID(.75, 70);
    liftClamp.spinToPosition(FRONT_CLAMP_DOWN, degrees, false);
    task::sleep(1000);
    driveBase.driveTilesPID(-0.52);
  }
  else
  {
    //get middle
    backClamp.spinToPosition(30, degrees, false);
    liftClamp.spinToPosition(FRONT_CLAMP_UP, degrees, false);
    driveBase.driveTilesPID(.87, 80);
    liftClamp.spinToPosition(FRONT_CLAMP_DOWN, degrees, false);
    task::sleep(1000);
    driveBase.driveTilesPID(-0.52);
    liftClamp.spinToPosition(FRONT_CLAMP_UP, degrees, true);
    //get alliance
    driveBase.turnDegreesAbsolutePID(-55);
    driveBase.driveTilesPID(-0.6,30);
    backClamp.spinToPosition(BACK_CLAMP_DOWN, degrees, false);
    task::sleep(1500); //to make sure the above doesn't stop the rest of the routine
    driveBase.driveTilesPID(0.16, 30);
    //score field rings
    lift.spinToPosition(120, degrees);
    driveBase.turnDegreesAbsolutePID(32);
    intake.spin(fwd,100,pct);
    driveBase.driveTilesPID(0.59,40);
    driveBase.driveTilesPID(-0.5, 50);
    //score match loads
    driveBase.turnDegreesAbsolutePID(210);
    liftClamp.spinToPosition(FRONT_CLAMP_CLEAR, degrees, false);
    lift.spinToPosition(180, degrees);
    scoreWithDelay(1500, .35, driveBase, 40000, matchTime);
    driveBase.turnDegreesAbsolutePID(50);
  }
}



void usercontrol(void) {
  MinesMotorGroup rightWheels(rightFront, rightTop, rightBack);
  MinesMotorGroup leftWheels(leftFront, leftTop, leftBack);
  FourWheelDrive driveBase(leftWheels, rightWheels, inertialSensor, master);

  MinesMotorGroup backClamp(leftBackClamp, rightBackClamp);
  MinesMotorGroup lift(leftLift, rightLift);

  driveBase.setAllBrakeMode(brakeType::coast);
  lift.setStopping(brakeType::hold);
  backClamp.setStopping(brakeType::hold);
  liftClamp.setStopping(brakeType::hold);

  driveBase.setTurnPIDConst(0.0092, 0.0001, 0.01);
  driveBase.setDrivePIDConst(4, 0.01, 0.0003);

  // User control code here, inside the loop
  while (1) {
    driveBase.arcadeLoopCall(master.Axis3.position(), master.Axis4.position());

    if (master.ButtonL1.pressing())
      {lift.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonL2.pressing())
      {lift.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {lift.stop();}

    if (master.ButtonR2.pressing())
      {intake.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonR1.pressing())
      {intake.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {intake.stop();}

    if (master.ButtonY.pressing())
      {backClamp.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonB.pressing())
      {backClamp.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {backClamp.stop();}

    if (master.ButtonA.pressing())
      {liftClamp.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonX.pressing())
      {liftClamp.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {liftClamp.stop();}


/*
      //auton test
    if (pressButton(master.ButtonUp.pressing(), upDebounce))
    {
      driveBase.driveTilesPID(1);
    }
    if (pressButton(master.ButtonDown.pressing(), downDebounce))
    {
      driveBase.driveTilesPID(-1);
    }
    if (pressButton(master.ButtonLeft.pressing(), leftDebounce))
    {
      driveBase.turnDegreesPID(-90);
    }
    if (pressButton(master.ButtonRight.pressing(), rightDebounce))
    {
      driveBase.turnDegreesPID(90);
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

