#include "main.h"

bool isMacro = false;


//HELPER FUNCTIONS
void setArm(int power) {
  arm = power;
}

void setIntake(int power) {
  intakeLeft = power;
  intakeRight = power;
}

void setTray(int power) {
  tray = power;
}


//MACROS
void stack() {
  setIntake(-10);
  tray.move_absolute(17100, 127);
  setIntake(0);
}

void towerLow() {
  tray.move_absolute(6300, 127);
  pros::delay(400);
  arm.move_absolute(4860, 127);
}

void towerHigh() {
  tray.move_absolute(7020, 127);
  pros::delay(400);
  arm.move_absolute(6480, 127);
}


//DRIVER CONTROL FUNCTIONS
void setArmMotor() {
  //R1 intakes, R2 outtakes
  int armPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  setArm(armPower);
}

void setIntakeMotors() {
  //R1 intakes, R2 outtakes
  int intakePower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntake(intakePower);
}

void setTrayMotor() {
  //R1 intakes, R2 outtakes
  int trayPower = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  setTray(trayPower);
}

void setArmTrayIntakeMotors(void* param) {
  while (1) {
    if (isMacro == 0) {
      setArmMotor();
      setIntakeMotors();
      setTrayMotor();
      //X to stack
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        isMacro = 1;
        stack();
        isMacro = 0;
      }
      //RIGHT to stack low tower
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        isMacro = 1;
        towerLow();
        isMacro = 0;
      }
      //LEFT to stack high tower
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        isMacro = 1;
        towerHigh();
        isMacro = 0;
      }
    }
  }
}
