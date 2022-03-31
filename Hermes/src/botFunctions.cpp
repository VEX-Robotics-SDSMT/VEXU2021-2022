#include "botFunctions.h"

void scoreWithDelay(int delay, double distance, FourWheelDrive driveBase)
{
  intake.spin(directionType::fwd);
  while(true)
  {
    task::sleep(delay);
    driveBase.driveTilesPID(distance);
    driveBase.driveTilesPID(-distance);
  }
}
void liftDown(bool waitForCompletion)
{
  liftClamp.spinToPosition(FRONT_CLAMP_DOWN, degrees, waitForCompletion);
}