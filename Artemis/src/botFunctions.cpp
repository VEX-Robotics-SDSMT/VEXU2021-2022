#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = true;
bool backMogoLiftUp = true;

void toggleFrontMogoLift(MinesMotorGroup &lift)
{
  int loops = 0;
  if (frontMogoLiftOpen)
  {
    //lift.spinToPosition(FRONT_MOGO_LIFT_DOWN, rotationUnits::deg, 100, velocityUnits::pct);
    lift.spin(vex::directionType::rev, 50, velocityUnits::pct);

    while(lift.rotation(deg) >= FRONT_MOGO_LIFT_DOWN && loops <= 3500)
    {
      loops += loopDelay;
      task::sleep(loopDelay);
    }
    frontMogoLiftOpen = false;
  }
  else
  {
    //lift.spinToPosition(FRONT_MOGO_LIFT_UP, rotationUnits::deg, 100, velocityUnits::pct);
    lift.spin(vex::directionType::fwd, 100, velocityUnits::pct);
    while(lift.rotation(deg) <= FRONT_MOGO_LIFT_UP && loops <= 3500)
    {
      loops += loopDelay;
      task::sleep(loopDelay);
    }
    frontMogoLiftOpen = true;
  }  
  lift.stop();
}

void toggleBackMogoArm(bool waitForCompletion)
{
  int loops = 0;
  if (backMogoLiftUp)
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_DOWN, rotationUnits::deg, 100, velocityUnits::pct, waitForCompletion);
    while(tailMotor.rotation(deg) >= BACK_MOGO_ARM_DOWN && loops <= 500)
    {
      loops += loopDelay;
      task::sleep(loopDelay);
    }
    backMogoLiftUp = false;
  }
  else 
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_UP, rotationUnits::deg, 100, velocityUnits::pct, waitForCompletion);
    while(tailMotor.rotation(deg) <= BACK_MOGO_ARM_UP && loops <= 500)
    {
      loops += loopDelay;
      task::sleep(loopDelay);
    }
    backMogoLiftUp = true;
  }  
}

void toggleBackMogoArm()
{
  toggleBackMogoArm(true);
}

void autoBalance(FourWheelDrive &drive, double distance, double speed)
{
  double pos = drive.getAllPosition();
  drive.accelerate(speed);

  while(Inertial.pitch() < 10 && drive.getAllPosition() - pos < distance)
  {
    task::sleep(20);
  }

  while(Inertial.pitch() > 10)
  {
    if (drive.getAllPosition() - pos > distance)
    {
      drive.accelerate(8);
    }
    task::sleep(20);
  }
  drive.accelerate(0);
}
