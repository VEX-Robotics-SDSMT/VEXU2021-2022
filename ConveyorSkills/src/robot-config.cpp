#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// drive motors
motor rightFront = motor(PORT8, ratio18_1, false);
motor rightBack = motor(PORT7, ratio18_1, false);
motor leftFront = motor(PORT2, ratio18_1, true);
motor leftBack = motor(PORT1, ratio18_1, true);

//other motors
motor rightShortLift = motor(PORT9, ratio36_1, false);
motor leftShortLift = motor(PORT3, ratio36_1, true);
motor rightTallLift = motor(PORT20, ratio18_1, true);
motor leftTallLift = motor(PORT5, ratio18_1, false);
motor intake = motor(PORT10, ratio18_1, false);
pneumatics hook = pneumatics(Brain.ThreeWirePort.H);

inertial Inertial = inertial(PORT13);
controller Master = controller();

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}