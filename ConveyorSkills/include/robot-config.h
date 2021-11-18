using namespace vex;

extern brain Brain;

// drivebase motors
extern motor rightFront;
extern motor rightBack;
extern motor leftFront;
extern motor leftBack;

extern motor rightShortLift;
extern motor leftShortLift;
extern motor rightTallLift;
extern motor leftTallLift;
extern motor intake;
extern pneumatics hook;

extern inertial Inertial;
extern controller Master;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );