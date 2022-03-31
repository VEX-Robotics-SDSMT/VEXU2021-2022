using namespace vex;

extern brain Brain;

// drivebase motors
extern motor rightDriveTop;
extern motor rightDriveMid;
extern motor rightDriveBottom;
extern motor leftDriveTop;
extern motor leftDriveMid;
extern motor leftDriveBottom;

extern motor rightFrontMogoLift;
extern motor leftFrontMogoLift;
extern motor right6Bar;
extern motor left6Bar;
extern motor rightChainBar;
extern motor leftChainBar;
extern motor backMogoArm;

extern inertial Inertial;
extern controller Master;

extern pneumatics plungerPneumatics;
extern pneumatics backMogoPnumatics;

extern pot rearMogoPot;
extern potV2 left6BarPot;
extern potV2 right6BarPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );