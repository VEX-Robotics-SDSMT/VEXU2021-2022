#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// drivebase motors
motor leftDrive1 = motor(PORT9, ratio18_1, true);
motor leftDrive2 = motor(PORT7, ratio18_1, false);
motor leftDrive3 = motor(PORT5, ratio18_1, false);
motor leftDrive4 = motor(PORT2, ratio18_1, true);
motor rightDrive1 = motor(PORT20, ratio18_1, false);
motor rightDrive2 = motor(PORT18, ratio18_1, true);
motor rightDrive3 = motor(PORT15, ratio18_1, true);
motor rightDrive4 = motor(PORT11, ratio18_1, false);

motor tailMotor = motor(PORT1, ratio6_1, false);
motor leftLiftMotor = motor(PORT8, ratio18_1, true);
motor rightLiftMotor = motor(PORT16, ratio18_1, false);

inertial Inertial = inertial(PORT16);
controller Master = controller();

pot rearPot = pot(Brain.ThreeWirePort.A);
pot leftPot = pot(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {}