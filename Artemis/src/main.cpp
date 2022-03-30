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
  snakeJaw.close();
  hornClamp.close();
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
  bool keepPulling = true;
  //commented out for scrim until it has been tuned
  
  MinesMotorGroup l(leftDrive1, leftDrive2, leftDrive3, leftDrive4);
  MinesMotorGroup r(rightDrive1, rightDrive2, rightDrive3, rightDrive4);
  MinesMotorGroup lift(leftLiftMotor, rightLiftMotor);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setAllBrakeMode(brakeType::brake);
  d.setTurnPIDConst(0.01, 0.01, 0.0001);
  d.setDrivePIDConst(.8, 0, 0);
  lift.setStopping(brakeType::hold);
  tailMotor.setStopping(brakeType::hold);


  if (skills)
  {
    tailMotor.stop();
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 100);
    d.driveTilesPID(.25);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_UP, 50); //pick up first alliance mobile goal
    d.turnDegreesAbsolutePID(-45);//90
    d.driveTilesPID(1);//.55
    d.turnDegreesAbsolutePID(25);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 100);
    d.driveTilesPID(.35);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_UP, 100);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 100);
    d.driveTilesPID(1.1);
    d.turnDegreesAbsolutePID(-50);
    d.driveTilesPID(.65);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_RING, 50);
    d.driveTilesPID(-.45);
    d.turnDegreesAbsolutePID(-170);
    d.driveTilesPID(1.2);
    d.turnDegreesAbsolutePID(-180);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 100);
    d.turnDegreesAbsolutePID(-60);
    d.driveTilesPID(.45);
    toggleHornClamp();
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_RING, 100);
    d.driveTilesPID(-.45);
    d.turnDegreesAbsolutePID(24);
    d.driveTilesPID(1.2);
    d.turnDegreesAbsolutePID(0);
    d.driveTilesPID(.5);
    d.turnDegreesAbsolutePID(-90);
    d.driveTilesPID(-.5, 75);
    d.driveTilesPID(.65, 50);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 100);
    autoBalance(d, 1, 100);
  }
  else
  {
    chargeGoal(d, 95, keepPulling);
    d.driveTilesPID(0.75);
    toggleSnakeJaw();
    task::sleep(300);
    d.turnDegreesAbsolutePID(-30);
    moveBackMogoArm(BACK_MOGO_ARM_UP, 80);
    d.turnDegreesAbsolutePID(0);
    d.driveTilesPID(0.3);
    d.turnDegreesAbsolutePID(-95);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_RING, 80);
    d.turnDegreesAbsolutePID(-195);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN,80);
    d.driveTilesPID(0.8);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_UP, 80);
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN,80);

    //toggleBackMogoArm();
    //d.setMotorsRelative(100, 100);
    //d.turnDegreesPID(180);
    //tailMotor.spinToPosition(0, rotationUnits::deg);
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
  bool manualArmMovement = false;

  Master.ButtonB.pressed(toggleBackMogoArm);
  Master.ButtonA.pressed(toggleSnakeJaw);
  Master.ButtonL1.pressed(toggleHornClamp);

  //TODO - move to a different function
  MinesMotorGroup l(leftDrive1, leftDrive2, leftDrive3, leftDrive4);
  MinesMotorGroup r(rightDrive1, rightDrive2, rightDrive3, rightDrive4);
  MinesMotorGroup lift(leftLiftMotor, rightLiftMotor);
  FourWheelDrive d(&l, &r, &Inertial, &Master);
  d.setDrivePIDConst(6.4, 0, 0.0024);
  d.setTurnPIDConst(0.0064, 0, 0.0002);

  d.setAllBrakeMode(brakeType::coast);
  lift.setStopping(brakeType::hold);

  // User control code here, inside the loop
  while (1) {
    d.arcadeLoopCall(Master.Axis3.position(), Master.Axis1.position());

    if (Master.ButtonR1.pressing())
    {
      lift.spin(directionType::fwd,100, percentUnits::pct);

    }
    else if (Master.ButtonR2.pressing())
    {
      lift.spin(directionType::rev,100, percentUnits::pct);
    }
    else 
    {
      lift.stop();
    }

    if (Master.ButtonDown.pressing() || Master.ButtonUp.pressing())
    {
      manualArmMovement = true;
    }

    if (manualArmMovement)
    {
      if (Master.ButtonUp.pressing())
      {
        tailMotor.spin(directionType::fwd, 50, percentUnits::pct);
      }
      else if (Master.ButtonDown.pressing())
      {
        tailMotor.spin(directionType::rev, 50, percentUnits::pct);
      }
      else
      {
        tailMotor.stop();
      }
    }

    //for testing purposes only
    /*if (pressButton(Master.ButtonUp.pressing(), buttonUpDebounce))
    {
      toggleFrontMogoLift(lift);
    }*/


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

