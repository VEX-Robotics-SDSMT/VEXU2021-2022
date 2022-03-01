#include "globals.h"

void moveLiftToPosition(MinesMotorGroup &lift, double pos, double speed);
void toggleFrontMogoLift(MinesMotorGroup&);
void toggleBackMogoArm(bool waitForCompletion);
void toggleBackMogoArm();
void toggleSnakeJaw();
void toggleHornClamp();

void autoBalance(FourWheelDrive &drive, double distance, double speed);
void chargeGoal(FourWheelDrive &drive, double dist);
