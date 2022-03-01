#include "globals.h"

void toggleFrontMogoLift(MinesMotorGroup&);
void toggleBackMogoArm(bool waitForCompletion);
void toggleBackMogoArm();
void toggleSnakeJaw();
void toggleHornClamp();

void autoBalance(FourWheelDrive &drive, double distance, double speed);
