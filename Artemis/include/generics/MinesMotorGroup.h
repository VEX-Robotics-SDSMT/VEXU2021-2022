#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include "vex.h"
#include <string>
#include <iostream>


class MinesMotorGroup : public motor_group 
{
  const rotationUnits ROT_UNITS = rotationUnits::deg;
  const int LOOP_DELAY = 20;

  double speed = 100;
  double tolerance = 5;
  double withinTargetTime = 20; 
  double timeout = 5000;
  double target = 0;
  //TODO should be tuned PERFECTLY because it will be reused over and over again
  double kp = 0.005;
  double ki = 0;
  double kd = 0.0001;

  bool runnningPId = false;

  //function pointer
  bool pointerFilled = false;
  double (*externalPositionFunc)(void);

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
    void setExternalPositionFunc(double (*func)());

    bool getTargetReached();
    bool getPIDRunning();
    double getPosition();

    void startMoveToPosition(double pos, double timeout, double tolerance);
    void startMoveToPosition(double pos, double s);
    void startHoldPosition(double pos);
};

#endif