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

//CONTROLLER
extern pros::Controller controller;

//VARIABLES
extern int macroRun;
#define TRAYVERTICAL 8700
#define TRAYLOW 4000
#define ARMLOW 2300
#define ARMHIGH 3000
