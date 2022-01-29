#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;



// drivebase motors
motor rightDriveTop = motor(PORT12, ratio6_1, false);
motor rightDriveMid = motor(PORT14, ratio6_1, true);
motor rightDriveBottom = motor(PORT15, ratio6_1, false);
motor leftDriveTop = motor(PORT1, ratio6_1, true);
motor leftDriveMid = motor(PORT4, ratio6_1, false);
motor leftDriveBottom = motor(PORT3, ratio6_1, true);

//lift motors
motor rightFrontMogoLift = motor(PORT18, ratio36_1, true);
motor leftFrontMogoLift = motor(PORT9, ratio36_1, false);
motor right6Bar = motor(PORT17, ratio18_1, true);
motor left6Bar = motor(PORT6, ratio18_1, false);
motor rightChainBar = motor(PORT13, ratio36_1, true);
motor leftChainBar = motor(PORT2, ratio36_1, false);
motor backMogoArm = motor(PORT10, ratio36_1, false);

pneumatics plungerPneumatics = pneumatics(Brain.ThreeWirePort.C);
pneumatics backMogoPnumatics = pneumatics(Brain.ThreeWirePort.F);

pot rearMogoPot = pot(Brain.ThreeWirePort.G);
pot left6BarPot = pot(Brain.ThreeWirePort.A);
pot right6BarPot = pot(Brain.ThreeWirePort.H);
pot leftChainPot = pot(Brain.ThreeWirePort.B);
pot rightChainPot = pot(Brain.ThreeWirePort.E);

inertial Inertial = inertial(PORT8);
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