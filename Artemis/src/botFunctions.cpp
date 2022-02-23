#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = false;
bool backMogoLiftUp = false;

void toggleFrontMogoLift(MinesMotorGroup &lift)
{
  if (frontMogoLiftOpen)
  {
    lift.spinToPosition(FRONT_MOGO_LIFT_DOWN, rotationUnits::deg, 100, velocityUnits::pct);
    frontMogoLiftOpen = false;
  }
  else
  {
    lift.spinToPosition(FRONT_MOGO_LIFT_UP, rotationUnits::deg, 100, velocityUnits::pct);
    frontMogoLiftOpen = true;
  }  
}

void toggleBackMogoArm(bool waitForCompletion)
{
  if (backMogoLiftUp)
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_DOWN, rotationUnits::deg, 100, velocityUnits::pct, waitForCompletion);
    backMogoLiftUp = false;
  }
  else 
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_UP, rotationUnits::deg, 100, velocityUnits::pct, waitForCompletion);
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
