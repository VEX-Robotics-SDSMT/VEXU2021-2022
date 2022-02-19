#include "globals.h"

void toggleFrontMogoLift();
void toggleBackMogoArm(bool waitForCompletion = true);

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

void autoBalance(FourWheelDrive &drive, double distance, double speed);
