#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include "vex.h"

class MinesMotorGroup : public motor_group 
{
  const rotationUnits ROT_UNITS = rotationUnits::deg;
  const int LOOP_DELAY = 20;
  float INTEGRATOR_MAX_MAGNITUDE = 1000;

  double speed = 0;
  double tolerance = 0.05;
  double toleranceTime = 500;
  double timeout = -1;
  double target = 0;
  double kp = 1;
  double ki = 0;
  double kd = 0.001;

  bool runnningPId = false;

  private:
    void startPID();
    void runPIDForever();
    void runPIDToPosition();
    void PIDOneLoop(double &lastE, double &lastI);
    double bindToMagnitude(double value, double MAX_MAGNITUDE);

  public:
    MinesMotorGroup(motor, motor);
    MinesMotorGroup(motor, motor, motor);
    MinesMotorGroup(motor, motor, motor, motor);

    void stopPID();

    void setPIDSpeed(double);
    void setPIDValues(double, double, double);

    bool getTargetReached();
    bool getPIDRunning();

    void startMoveToPosition(double pos, double timeout, double tolerance);
    void startHoldPosition(double pos);

};

#endif