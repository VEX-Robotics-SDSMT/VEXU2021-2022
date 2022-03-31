#include "globals.h"

void toggleFrontMogoLift();
void toggleBackMogoArm(bool waitForCompletion);
void toggleBackMogoArm();

//plunger arm
void togglePlunger();
void movePlungerPos(const double[3], bool waitForCompletion = true);

void movePlungerOpen();
void movePlungerHome();
void movePlungerRest();
void movePlungerScore();
void movePlungerPrep();
void movePlungerPlunge();
void plungeRing();
void plungeUntilTime(int delay, int time, int startTime);
double getPotPos();
double get6BarPots();

void autoBalance(FourWheelDrive &drive, double distance, double speed);
void chargeGoal(FourWheelDrive &drive, double dist);

