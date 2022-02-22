#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftUp = false;
bool sixBarUp = true;
bool backMogoLiftUp = false;

void toggleFrontMogoLift()
{
  if (frontMogoLiftUp)
  {
    frontMogoLift->spinToPosition(FRONT_MOGO_LIFT_DOWN, rotationUnits::deg);
    frontMogoLiftUp = false;
  }
  else if (sixBarUp)
  {
    frontMogoLift->spinToPosition(FRONT_MOGO_LIFT_UP, rotationUnits::deg);
    frontMogoLiftUp = true;
  }  
}

void toggleBackMogoArm(bool waitForCompletion)
{
    if (backMogoLiftUp)
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_DOWN, rotationUnits::deg, waitForCompletion);
    backMogoLiftUp = false;
  }
  else 
  {
    tailMotor.spinToPosition(BACK_MOGO_ARM_UP, rotationUnits::deg, waitForCompletion);
    backMogoLiftUp = true;
  }  
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
