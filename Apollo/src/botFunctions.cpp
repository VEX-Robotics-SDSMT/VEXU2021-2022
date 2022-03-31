#include "../include/botFunctions.h"

//globals for this file only
bool frontMogoLiftOpen = false;
bool sixBarUp = true;
bool backMogoLiftUp = false;

double getPotPos()
{
  double pos = (POT_ADD + right6BarPot.value(analogUnits::range12bit)) * POT_MULT; 
  return pos;
}

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
  int loops = 0;
  if (backMogoLiftUp)
  {
    backMogoArm.spin(directionType::rev, 100, velocityUnits::pct);
    while(fabs(backMogoArm.rotation(deg) - BACK_MOGO_LIFT_DOWN) >= 5 && loops <= 500)
    {
      loops += loopDelay;
      task::sleep(loopDelay);
    }
    backMogoArm.stop();
    backMogoLiftUp = false;
  }
  else 
  {
    
    backMogoArm.spinToPosition(BACK_MOGO_LIFT_UP, rotationUnits::deg, waitForCompletion);
    backMogoLiftUp = true;
  }  
}

void toggleBackMogoArm()
{
  toggleBackMogoArm(true);
}

void togglePlunger()
{
  plungerPneumatics.set( !plungerPneumatics.value());
}

void movePlungerPos(const double armPair[3], bool waitForCompletion)
{
  if (armPair[2] >= 0)
  {
    sixBarLift->spinToPosition(armPair[0], rotationUnits::deg, 50, velocityUnits::pct, false);
    task::sleep(armPair[2]);
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 50, velocityUnits::pct, waitForCompletion);
  }
  else
  {
    chainLift->spinToPosition(armPair[1], rotationUnits::deg, 50, velocityUnits::pct, false);
    task::sleep(armPair[2]);
    sixBarLift->spinToPosition(armPair[0], rotationUnits::deg, 50, velocityUnits::pct, waitForCompletion);
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

void plungeUntilTime(int delay, int time, int startTime)
{
  time = startTime + time - delay; //this is here to make sure this doesn't go overtime
  while(Brain.Timer.time() < time)
  {
    task::sleep(delay);
    plungeRing();
  }
}

void chargeGoal(FourWheelDrive &drive, double dist)
{
  toggleBackMogoArm(false);
  drive.setMotors(-100);
  int count = 0;
  while (drive.getAllPosition() > -dist) //(drive.getAllPosition() > -dist)
  {
    task::sleep(loopDelay);
    Brain.Screen.clearLine(0);
    Brain.Screen.print(count);
    count++;
  }
  toggleBackMogoArm();
  drive.setMotors(0);
  Brain.Screen.print(drive.getAllPosition());
}

double get6BarPots()
{
  double angle = right6BarPot.angle(rotationUnits::deg);
  angle += left6BarPot.angle(rotationUnits::deg);
  angle /= 2;

  return angle;
}

