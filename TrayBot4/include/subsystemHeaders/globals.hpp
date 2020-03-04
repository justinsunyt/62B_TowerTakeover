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

//CONTROLLER
extern pros::Controller controller;

//VARIABLES
extern int macroRun;
extern int isMacro;
extern int auton;

//POSITIONS
#define TRAYVERTICAL 4200
#define ARMLOW 2300
#define ARMHIGH 3000

//OP CONTROL CONSTANTS
#define ARMPOWER 127
#define INTAKEPOWER 127
#define TRAYPOWER 90
#define OUTTAKERATIO 0.7

//AUTON CONSTANTS
#define MOVEVELOCITY 130
#define TURNVELOCITY 100
