#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = true;
bool backMogoLiftUp = true;
bool jawOpen = false;
bool hornClampOpen = false;

void toggleFrontMogoLift(MinesMotorGroup &lift)
{

  if (frontMogoLiftOpen)
  {
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_DOWN, 50);
    frontMogoLiftOpen = false;
  }
  else
  {
    moveLiftToPosition(lift, FRONT_MOGO_LIFT_UP, 50);
    frontMogoLiftOpen = true;
  }  
}

void moveLiftToPosition(MinesMotorGroup &lift, double pos, double speed)
{
  directionType dir = directionType::fwd;

  if(lift.rotation(deg) > pos )
    dir = directionType::rev;

  int loops = 0;
  lift.spin(dir, speed, velocityUnits::pct);

  while(fabs(lift.rotation(deg) - pos) >= 20 && loops <= 3500)
  {
    loops += loopDelay;
    task::sleep(loopDelay);
  }
  lift.stop();
}

void toggleSnakeJaw()
{
  if (jawOpen)
  {
    snakeJaw.close();
    jawOpen = false;
  }
  else
  {
    snakeJaw.open();
    jawOpen = true;
  }
}

void toggleHornClamp()
{
  if (hornClampOpen)
  {
    hornClamp.close();
    hornClampOpen = false;
  }
  else
  {
    hornClamp.open();
    hornClampOpen = true;
  }
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

void chargeGoal(FourWheelDrive &drive, double dist)
{
  tailMotor.spin(reverse, 100, velocityUnits::pct);
  drive.setMotors(-100);
  while (drive.getAllPosition() > -dist)
  {
    task::sleep(loopDelay);
  }
  tailMotor.stop(); 
  drive.setMotors(100);
  while (drive.getAllPosition() < -(dist-100))
  {
    task::sleep(loopDelay);
  }
  drive.setMotors(0);
}
