using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor rightFront;
extern motor rightMid;
extern motor rightBack;
extern motor leftFront;
extern motor leftMid;
extern motor leftBack;
extern inertial Inertial;
extern motor_group rightMotors;
extern motor_group leftMotors;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );