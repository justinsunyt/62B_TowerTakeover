#include "main.h"

//MOTORS
extern pros::Motor arm;
extern pros::Motor intakeLeft;
extern pros::Motor intakeRight;
extern pros::Motor tray;
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightFront;

//SENSORS
extern pros::ADIDigitalIn trayLimit;
extern pros::ADIDigitalIn armLimit;
extern pros::Imu inertial;

//CONTROLLER
extern pros::Controller controller;

//VARIABLES
extern int macroRun;
extern int isMacro;
extern int auton;

//POSITIONS
#define TRAYLOW 2000
#define TRAYVERTICAL 4200
#define ARMLOW 1960
#define ARMHIGH 2800

//OP CONTROL CONSTANTS
#define ARMPOWER 127
#define INTAKEPOWER 127
#define TRAYPOWER 90
#define HIGHINTAKE 105
#define LOWINTAKE 80

//AUTON CONSTANTS
#define SLOWMOVE 30
#define MOVE 110
#define INTAKEMOVE 85
#define TURN 80
