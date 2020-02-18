#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  pros::task_t armTrayIntake = pros::c::task_create(setArmTrayIntakeMotors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "armTrayIntake");
  pros::Task armTrayIntakeTask (armTrayIntake);
  pros::task_t drive = pros::c::task_create(setDriveMotors, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drive");
  pros::Task driveTask (setDriveMotors);
  while(true) {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      macroRun = 0;
      pros::delay(10);
      macroRun = 1;
      isMacro = 0;
    }
  }
}
