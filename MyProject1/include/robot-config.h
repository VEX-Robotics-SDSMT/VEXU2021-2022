using namespace vex;

extern brain Brain;
extern controller Master;

// VEXcode devices
extern motor rightFront;
extern motor rightMid;
extern motor rightBack;
extern motor leftFront;
extern motor leftMid;
extern motor leftBack;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );