#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = false;
bool sixBarUp = true;
bool backMogoLiftUp = false;

void toggleFrontMogoLift()
{
  if (frontMogoLiftOpen)
  {
    frontMogoLift->spinToPosition(FRONT_MOGO_LIFT_IN, rotationUnits::deg);
    frontMogoLiftOpen = false;
  }
  else if (sixBarUp)
  {
    frontMogoLift->spinToPosition(FRONT_MOGO_LIFT_OUT, rotationUnits::deg);
    frontMogoLiftOpen = true;
  }  
}

void toggleBackMogoArm(bool waitForCompletion)
{
    if (backMogoLiftUp)
  {
    backMogoArm.spinToPosition(BACK_MOGO_LIFT_DOWN, rotationUnits::deg, waitForCompletion);
    backMogoLiftUp = false;
  }
  else 
  {
    backMogoArm.spinToPosition(BACK_MOGO_LIFT_UP, rotationUnits::deg, waitForCompletion);
    backMogoLiftUp = true;
  }  
}

void togglePlunger()
{
  plungerPneumatics.set( !plungerPneumatics.value());
}

void movePlungerPos(const double armPair[3], bool waitForCompletion)
{
  if (armPair[2] >= 0)
  {
    sixBarLift->spinToPosition(armPair[0], rotationUnits::deg, false);
    task::sleep(armPair[2]);
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 50, velocityUnits::pct, waitForCompletion);
  }
  else
  {
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 50, velocityUnits::pct, false);
    task::sleep(armPair[2]);
    sixBarLift->spinToPosition(armPair[0], rotationUnits::deg, waitForCompletion);
  }
}

void movePlungerOpen()
{
  movePlungerPos(PLUNGE_OPEN);
}

void movePlungerHome()
{
  movePlungerPos(PLUNGE_HOME, true);
  task::sleep(300);
  plungerPneumatics.close();
}

void movePlungerRest()
{
  movePlungerPos(PLUNGE_REST);
}

void movePlungerScore()
{
  movePlungerPos(PLUNGE_SCORE);
  task::sleep(150);
  plungerPneumatics.open();
  task::sleep(1500);
  plungerPneumatics.close();
  movePlungerOpen();
}

void movePlungerPrep()
{
  movePlungerPos(PLUNGE_PREP);
}

void movePlungerPlunge()
{
  movePlungerPos(PLUNGE_PLUNGE);
}

void plungeRing()
{
  movePlungerPos(PLUNGE_PREP, true);
  movePlungerPos(PLUNGE_PLUNGE, true);
  movePlungerPos(PLUNGE_PREP, true);
}

void autoBalance(FourWheelDrive &drive, double distance, double speed)
{
  double pos = drive.getAllPosition();

  movePlungerPos(PLUNGE_OPEN, true);
  task::sleep(1000);
  movePlungerPos(PLUNGE_PLUNGE, true);
  chainLift->setStopping(brakeType::coast);
  task::sleep(500);


  drive.accelerate(speed);

  while(Inertial.pitch() < 10 || drive.getAllPosition() - pos < distance)
  {
    task::sleep(20);
  }

  movePlungerRest();
  chainLift->setStopping(brakeType::brake);

  while(Inertial.pitch() > 10)
  {
    if (drive.getAllPosition() - pos > distance)
    {
      drive.accelerate(4);
    }
    task::sleep(20);
  }
  drive.accelerate(0);
}

void plungeUntilTime(int delay, int time)
{
  time = time - delay; //this is here to make sure this doesn't go overtime
  while(Brain.Timer.time() < time)
  {
    task::sleep(delay);
    plungeRing();
  }
}
