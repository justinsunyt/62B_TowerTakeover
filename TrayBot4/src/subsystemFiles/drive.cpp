#include "main.h"

//HELPER FUNCTIONS
void setDrive(int left, int right) {
  driveLeftBack = left;
  driveLeftFront = left;
  driveRightBack = right;
  driveRightFront = right;
}

void coastDrive() {
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void holdDrive() {
  driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

//DRIVER CONTROL FUNCTIONS
void setDriveMotors(void* param) {
  while(true) {
    int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    if(abs(leftJoystick) < 10)
      leftJoystick = 0;
    if(abs(rightJoystick) < 10)
      rightJoystick = 0;

    setDrive(leftJoystick, rightJoystick);
  }
}
