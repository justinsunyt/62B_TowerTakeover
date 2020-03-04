#include "main.h"


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
  double trayPower = 127;
  double exp = 0;
  setIntake(0);
  while (tray.get_position() < TRAYVERTICAL && macroRun == 1) {
    tray = trayPower;
    pros::delay(10);
    if (trayPower > 60) {
      exp += 0.012;
      trayPower = trayPower - exp * exp * exp;
    }
  }
}

void towerLow() {
  setIntake(-80);
  pros::delay(200);
  arm.move_absolute(ARMLOW, 127);
  pros::delay(150);
  setIntake(0);
  while (arm.get_position() < ARMLOW && macroRun == 1) {
    pros::delay(2);
  }
}

void towerHigh() {
  setIntake(-80);
  pros::delay(200);
  arm.move_absolute(ARMHIGH, 127);
  pros::delay(150);
  setIntake(0);
  while (arm.get_position() < ARMHIGH && macroRun == 1) {
    pros::delay(2);
  }
}

void resetArmTray() {
  while ((!armLimit.get_value() || !trayLimit.get_value()) && macroRun) {

   if (trayLimit.get_value()) {
     tray = 0;
   }
   else
   {
     tray = -127;
   }
   if (armLimit.get_value()) {
     arm = 0;
   }
   else
   {
     arm = -127;
   }
   pros::delay(2);
  }
  tray = 0;
  arm = 0;
  if (macroRun == 1) {
   tray.tare_position();
   arm.tare_position();
  }
}

void deploy() {
  setIntake(-127);
  pros::delay(200);
  setArm(127);
  pros::delay(200);
  resetArmTray();
  setIntake(0);
}


//DRIVER CONTROL FUNCTIONS
void setArmMotor() {
  int armPower;
  //UP moves arm up, DOWN moves arm down
  if (armLimit.get_value()) {
    armPower = ARMPOWER * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP));
  } else {
    armPower = ARMPOWER * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  }
  setArm(armPower);
}

void setIntakeMotors() {
  //R1 intakes, R2 outtakes
  int intakePower = INTAKEPOWER * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - OUTTAKERATIO * controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  setIntake(intakePower);
}

void setTrayMotor() {
  //L1 moves tray in, L2 moves tray out
  int trayPower;
  if (trayLimit.get_value()) {
    trayPower = TRAYPOWER * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
  } else {
    trayPower = TRAYPOWER * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1));
  }
  setTray(trayPower);
}

void setArmTrayIntakeMotors(void* param) {
  while(true) {
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
      //A to reset
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        isMacro = 1;
        resetArmTray();
        isMacro = 0;
      }
      //Y to deploy
      if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
        isMacro = 1;
        deploy();
        isMacro = 0;
      }
    }
  }
}
