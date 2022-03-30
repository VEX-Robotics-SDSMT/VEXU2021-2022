using namespace vex;

extern brain Brain;

// drivebase motors
extern motor rightDrive1;
extern motor rightDrive2;
extern motor rightDrive3;
extern motor rightDrive4;
extern motor leftDrive1;
extern motor leftDrive2;
extern motor leftDrive3;
extern motor leftDrive4;

extern motor tailMotor;
extern motor leftLiftMotor;
extern motor rightLiftMotor;

extern inertial Inertial;
extern controller Master;
extern sonar rangeFinder;

extern pneumatics snakeJaw;
extern pneumatics hornClamp;

extern potV2 liftPot;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );