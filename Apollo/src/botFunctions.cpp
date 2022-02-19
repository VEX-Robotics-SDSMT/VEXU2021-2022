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
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 30, velocityUnits::pct, waitForCompletion);
  }
  else
  {
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 30, velocityUnits::pct, false);
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
  plungerPneumatics.close();
  task::sleep(1000);
  movePlungerPos(PLUNGE_PLUNGE, true);
  plungerPneumatics.open();
  task::sleep(1000);
  movePlungerPos(PLUNGE_PREP, true);
}
