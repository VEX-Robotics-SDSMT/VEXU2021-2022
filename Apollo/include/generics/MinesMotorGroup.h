#ifndef _MINES_MOTOR_GROUP
#define _MINES_MOTOR_GROUP

#include "vex.h"

class MinesMotorGroup : public motor_group 
{
  public:
    MinesMotorGroup(motor, motor);
    MinesMotorGroup(motor, motor, motor);
    MinesMotorGroup(motor, motor, motor, motor);
};

#endif