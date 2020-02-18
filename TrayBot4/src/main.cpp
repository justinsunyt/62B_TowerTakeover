#include "main.h"

//AUTON SWITCH
void printAuton() {
	pros::lcd::set_text(3, "Auton:");
	if (auton == 0) {
		pros::lcd::set_text(4, "One Point");
	}
	else if (auton == 1) {
		pros::lcd::set_text(4, "Skills");
	}
	else if (auton == 2) {
		pros::lcd::set_text(4, "Red Protected");
	}
	else if (auton == 3) {
		pros::lcd::set_text(4, "Blue Protected");
	}
	else if (auton == 4) {
		pros::lcd::set_text(4, "Red UnProtected");
	}
	else if (auton == 5) {
		pros::lcd::set_text(4, "Blue UnProtected");
	}
}

void autonSwitchLeft() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		if (auton == 0) {
			auton = 5;
		} else {
			auton -= 1;
		}
		printAuton();
	}
}
void autonSwitchRight() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		if (auton == 5) {
			auton = 0;
		} else {
			auton += 1;
		}
		printAuton();
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Dank Mobile");
	printAuton();
	pros::lcd::register_btn0_cb(autonSwitchLeft);
	pros::lcd::register_btn2_cb(autonSwitchRight);

	driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	tray.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	tray.tare_position();
	arm.tare_position();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
