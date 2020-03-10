#include "main.h"

//MOTORS
pros::Motor arm(6, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeLeft(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intakeRight(9, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor tray(5, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(3, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS);

//SENSORS
pros::ADIDigitalIn trayLimit('A');
pros::ADIDigitalIn armLimit('B');

//CONTROLLER_MASTER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

int macroRun = 1;
int isMacro = 0;
int auton = 0;
