#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;



// drivebase motors
motor rightDriveTop = motor(PORT1, ratio6_1, false);
motor rightDriveMid = motor(PORT4, ratio6_1, true);
motor rightDriveBottom = motor(PORT3, ratio6_1, false);

motor leftDriveTop = motor(PORT19, ratio6_1, true);
motor leftDriveMid = motor(PORT21, ratio6_1, false);
motor leftDriveBottom = motor(PORT15, ratio6_1, true);

//lift motors
motor rightFrontMogoLift = motor(PORT20, ratio36_1, true);
motor leftFrontMogoLift = motor(PORT9, ratio36_1, false);
motor right6Bar = motor(PORT17, ratio18_1, false);
motor left6Bar = motor(PORT7, ratio18_1, true);
motor rightChainBar = motor(PORT13, ratio36_1, true);
motor leftChainBar = motor(PORT11, ratio36_1, false);
motor backMogoArm = motor(PORT10, ratio36_1, true);

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
void vexcodeInit( void ) {}