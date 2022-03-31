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

motor leftDriveTop = motor(PORT20, ratio6_1, true);
motor leftDriveMid = motor(PORT21, ratio6_1, false);
motor leftDriveBottom = motor(PORT19, ratio6_1, true);

//lift motors
motor rightFrontMogoLift = motor(PORT9, ratio36_1, false);
motor leftFrontMogoLift = motor(PORT6, ratio36_1, true);
motor right6Bar = motor(PORT11, ratio18_1, true);
motor left6Bar = motor(PORT17, ratio18_1, false);
motor rightChainBar = motor(PORT12, ratio36_1, true);
motor leftChainBar = motor(PORT15, ratio36_1, false);
motor backMogoArm = motor(PORT10, ratio36_1, true);

pneumatics plungerPneumatics = pneumatics(Brain.ThreeWirePort.C);
pneumatics backMogoPnumatics = pneumatics(Brain.ThreeWirePort.F);

pot rearMogoPot = pot(Brain.ThreeWirePort.G);
potV2 left6BarPot = potV2(Brain.ThreeWirePort.H);
potV2 right6BarPot = potV2(Brain.ThreeWirePort.A);

inertial Inertial = inertial(PORT2);
controller Master = controller();

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {}