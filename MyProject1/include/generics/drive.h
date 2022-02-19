#ifndef _FOUR_WHEEL_DRIVE
#define _FOUR_WHEEL_DRIVE

#define ONE_SEC_IN_MS 1000.0

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "vex.h"
#include "MinesMotorGroup.h"

class FourWheelDrive
{
    MinesMotorGroup *rightMotors;
    MinesMotorGroup *leftMotors;
    vex::inertial *inertialSensor;
    vex::controller *master;

    //calibration values
    std::stringstream fileStream;
    //these values are observed from the routine in the past
    //they will work if the file input fails, but not as well
    double maxSpeed = 128;
    double midSpeed = 69;
    double minSpeed = 10;
    double speedBias = 1;

    double LRBiasHigh = 1;
    double LRBiasLow = 1;
    double LRBiasHighBack = 1;
    double LRBiasLowBack = 1;
    double maxAccelerationForward = 3;
    double maxAccelerationBackward = 3;

    const double ROTATION_MUL = 845;
    const int STOP_AMOUNT = 100;
    const int LOOP_DELAY = 20;
    const rotationUnits ROT_UNIT = rotationUnits::deg;
    const velocityUnits VEL_UNIT = velocityUnits::pct;
    const brakeType BRAKE_MODE = brakeType::brake;

    const int turnThreshold = 5;
	  const int driveThreshold = 5;

    //default PID values
    double driveKP = 2.3;
    double driveKI = 0;
    double driveKD = 0.0036;
    double turnKP = 0.01; //speed to goal
    double turnKI = 0; //adds speed if too slow
    double turnKD = 0; //prevents overshoot

public:
    FourWheelDrive(MinesMotorGroup&, MinesMotorGroup&,
        vex::inertial&, vex::controller&);
    FourWheelDrive(MinesMotorGroup*, MinesMotorGroup*, vex::inertial*, vex::controller*);

    void setDrivePIDConst(double, double, double);
    void setTurnPIDConst(double, double, double);
    void accelerate(double speed);
    void setMotorsRelative(MinesMotorGroup *motors, double distance, double speed);
    void setMotorsRelative(double distance, double speed);
    void setAllBrakeMode(vex::brakeType mode);
    double getSpeed(MinesMotorGroup *);
    double getAllSpeed();
    double getAllPosition();
    double getPosition(MinesMotorGroup * motors);

    void drive(MinesMotorGroup *leftWheelMotorVector,
        MinesMotorGroup *rightWheelMotorVector, int distance);
    void driveTilesPID(float numTiles, float desiredSpeed= 75);
    void turnDegreesAbsolutePID(float targetDegrees, float desiredSpeed = -1);
    void turnDegreesPID(float numDegrees, float desiredSpeed= 55);

    void tankLoopCall(double, double);
    void arcadeLoopCall(double, double);



private:
    void rawSetMotors(double speed, double bias = 1);
    void setMotors(MinesMotorGroup *motors, double speed);
    void setMotors(double speed);
    void setZeroPosition(MinesMotorGroup * motors);
    void setZeroPosition();

    float degreeBoundingHelper(float inDegrees);
    float degreesToRadians(float radians);
    float radiansToDegrees(float degrees);
    float bindToMagnitude(float value, float MAX_MAGNITUDE);
    void setAllBrakeMode(MinesMotorGroup *motors, vex::brakeType mode);
    void setMotorPercents(int leftSpeed, int rightSpeed);
};


#endif
