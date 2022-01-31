#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = false;
bool sixBarUp = true;
bool chainLiftOut = false;
bool backMogoLiftUp = true;
bool plungerOpen = false;

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

void toggleSixBarLift()
{
  if (sixBarUp)
  {
    sixBarLift->spinToPosition(FRONT_SIXBAR_LIFT_DOWN, rotationUnits::deg);
    sixBarUp = false;
  }
  else 
  {
    sixBarLift->spinToPosition(FRONT_SIXBAR_LIFT_UP, rotationUnits::deg);
    sixBarUp = true;
  } 
}

void toggleBackMogoLift()
{
  if (backMogoLiftUp)
  {
    backMogoPnumatics.open();
    backMogoArm.spinToPosition(BACK_MOGO_LIFT_DOWN, rotationUnits::deg);
    backMogoLiftUp = false;
  }
  else 
  {
    backMogoPnumatics.close();
    backMogoArm.spinToPosition(BACK_MOGO_LIFT_UP, rotationUnits::deg);
    backMogoLiftUp = true;
  }  
}

void toggleChainLift()
{
  if (chainLiftOut)
  {
    chainLift->spinToPosition(CHAIN_LIFT_IN, rotationUnits::deg);
    chainLiftOut = false;
  }
  else 
  {
    chainLift->spinToPosition(CHAIN_LIFT_OUT, rotationUnits::deg);
    chainLiftOut = true;
  }  
}

void togglePlunger()
{
  if (plungerOpen)
  {
    plungerPneumatics.close();
  }
  else 
  {
    plungerPneumatics.open();
  }  
}

void startUp()
{
  sixBarLift->spinToPosition(FRONT_SIXBAR_LIFT_UP, rotationUnits::deg);
}


