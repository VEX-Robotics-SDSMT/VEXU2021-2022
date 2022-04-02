#include "botFunctions.h"

void scoreWithDelay(int delay, double distance, FourWheelDrive &driveBase)
{
  intake.spin(directionType::fwd);
  while(true)
  {
    task::sleep(delay);
    driveBase.driveTilesPID(distance, 50);
    driveBase.driveTilesPID(-distance, 50);
  }
}

void scoreWithDelay(int delay, double distance, FourWheelDrive &driveBase, int time, int startTime)
{
  time = startTime + time - delay + 3000; //this is here to make sure this doesn't go overtime
  while(Brain.Timer.time() < time)
  {
    task::sleep(delay);
    driveBase.driveTilesPID(distance, 75);
    driveBase.driveTilesPID(-distance, 75);
  }
}
