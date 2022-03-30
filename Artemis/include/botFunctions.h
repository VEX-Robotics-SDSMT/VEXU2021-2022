#include "globals.h"

double getPotPos();

void moveLiftToPosition(MinesMotorGroup &lift, double pos, double speed);
void toggleFrontMogoLift(MinesMotorGroup&);
void moveBackMogoArm(double pos, double speed);
void toggleBackMogoArm(bool waitForCompletion);
void toggleBackMogoArm();
void openJaw();
void toggleSnakeJaw();
void toggleHornClamp();

void autoBalance(FourWheelDrive &drive, double distance, double speed);
void chargeGoal(FourWheelDrive &drive, double dist, bool);