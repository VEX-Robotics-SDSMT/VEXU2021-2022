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
//#include "botFunctions.h"
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
  bool skills = true;
  //commented out for scrim until it has been tuned
  
  /*drive.setAllBrakeMode(brakeType::brake);
  d.setTurnPIDConst(0.01, 0.01, 0.0001);
  d.setDrivePIDConst(.8, 0, 0);
  lift.setStopping(brakeType::hold);
  tailMotor.setStopping(brakeType::hold);*/


  if (skills)
  {

  }
  else
  {

  }
}



void usercontrol(void) {
  //driveBase.setAllBrakeMode(brakeType::coast);
  MinesMotorGroup rightWheels(rightFront, rightTop, rightBack);
  MinesMotorGroup leftWheels(leftFront, leftTop, leftBack);
  FourWheelDrive driveBase(leftWheels, rightWheels, inertialSensor, master);

  MinesMotorGroup backClamp(leftBackClamp, rightBackClamp);
  MinesMotorGroup lift(leftLift, rightLift);

  lift.setStopping(brakeType::hold);
  backClamp.setStopping(brakeType::hold);
  liftClamp.setStopping(brakeType::hold);

  // User control code here, inside the loop
  while (1) {
    driveBase.arcadeLoopCall(master.Axis3.position(), master.Axis4.position());

    if (master.ButtonL1.pressing())
      {lift.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonL2.pressing())
      {lift.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {lift.stop();}

    if (master.ButtonR1.pressing())
      {intake.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonR2.pressing())
      {intake.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {intake.stop();}

    if (master.ButtonB.pressing())
      {backClamp.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonY.pressing())
      {backClamp.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {backClamp.stop();}

    if (master.ButtonA.pressing())
      {liftClamp.spin(directionType::fwd,100, percentUnits::pct);}
    else if (master.ButtonX.pressing())
      {liftClamp.spin(directionType::rev,100, percentUnits::pct);}
    else 
      {liftClamp.stop();}

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

