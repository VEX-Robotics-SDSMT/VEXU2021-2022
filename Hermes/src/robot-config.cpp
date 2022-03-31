#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
controller master = controller();

//port 6 & 8 are broke
// VEXcode device constructors
motor rightFront = motor(PORT15, ratio18_1, true);
motor rightTop = motor(PORT16, ratio18_1, true);
motor rightBack = motor(PORT18, ratio18_1, false);
motor leftFront = motor(PORT14, ratio18_1, false);
motor leftTop = motor(PORT17, ratio18_1, false);
motor leftBack = motor(PORT20, ratio18_1, true);
motor rightBackClamp = motor(PORT1, ratio36_1, true);
motor leftBackClamp = motor(PORT3, ratio36_1, false);
motor rightLift = motor(PORT2, ratio36_1, false);
motor leftLift = motor(PORT5, ratio36_1, true);
motor intake = motor(PORT11, ratio6_1, true);
motor liftClamp = motor(PORT7, ratio36_1, false);

inertial inertialSensor = inertial(PORT19);
potV2 rightPot = potV2(Brain.ThreeWirePort.H);
potV2 leftPot = potV2(Brain.ThreeWirePort.G);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}