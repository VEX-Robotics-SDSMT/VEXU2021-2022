
using namespace vex;

extern brain Brain;
extern controller master;

// VEXcode devices
extern motor rightFront;
extern motor rightTop;
extern motor rightBack;
extern motor leftFront;
extern motor leftTop;
extern motor leftBack;
extern motor rightBackClamp;
extern motor leftBackClamp;
extern motor rightLift;
extern motor leftLift;
extern motor intake;
extern motor liftClamp;

extern inertial inertialSensor;
extern potV2 rightPot;
extern potV2 leftPot;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );