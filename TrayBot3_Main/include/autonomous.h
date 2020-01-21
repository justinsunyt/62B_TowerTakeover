#include "vex.h"
#include "config.h"
#include "usercontrol.h"

using namespace vex;


void encoderDrive(float rev, float pct, bool wait) {
  LeftMotor1.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  LeftMotor2.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  RightMotor1.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);

  if (wait) {
    RightMotor2.spinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
  else {
    RightMotor2.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
}

void leftDrive(float rev, float pct, bool wait) {
  LeftMotor1.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);

  if (wait) {
    LeftMotor2.spinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
  else {
    LeftMotor2.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
}

void rightDrive(float rev, float pct, bool wait) {
  RightMotor1.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);

  if (wait) {
    RightMotor2.spinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
  else {
    RightMotor2.startSpinFor(directionType::fwd, rev, rotationUnits::rev, pct, velocityUnits::pct);
  }
}
 
void brakeDrive() {
  LeftMotor1.stop(brakeType::brake);
  LeftMotor2.stop(brakeType::brake);
  RightMotor1.stop(brakeType::brake);
  RightMotor2.stop(brakeType::brake);
}

void spinIntakes(bool dir, float pct) {
  if (dir) {
    RightIntakeMotor.spin(directionType::fwd, pct, velocityUnits::pct);
    LeftIntakeMotor.spin(directionType::fwd, pct, velocityUnits::pct);
  }
  else {
    RightIntakeMotor.spin(directionType::rev, pct, velocityUnits::pct);
    LeftIntakeMotor.spin(directionType::rev, pct, velocityUnits::pct);
  }
}

void brakeIntakes() {
  RightIntakeMotor.stop(brakeType::brake);
  LeftIntakeMotor.stop(brakeType::brake);
}

void deploy() {
  spinIntakes(true, 100);
  TrayMotor.startSpinFor(directionType::fwd, 1, rotationUnits::rev, 100, velocityUnits::pct);
  ArmMotor.spinFor(directionType::rev, 1.1, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  
  brakeIntakes();
  
  TrayMotor.startSpinFor(directionType::rev, 1, rotationUnits::rev, 100, velocityUnits::pct);
  ArmMotor.spinFor(directionType::fwd, 1.15, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
}

void onePointAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(2, 80, true);
  encoderDrive(-3, 80, true);
  brakeDrive();
}

void blueProtecAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);

  spinIntakes(true, 100);
  encoderDrive(1, 80, true);
  brakeDrive();
  wait(50, msec);

  encoderDrive(1.3, 45, true);
  brakeDrive();
  wait(100, msec);

  rightDrive(1.3, 40, false);
  leftDrive(-1.3, 40, true);
  wait(200, msec);

  encoderDrive(0.7, 45, true);
  wait(100, msec);

  leftDrive(-0.2, 40, true);
  encoderDrive(-3.2, 80, true);
  wait(100, msec);

  rightDrive(1.2, 40, false);
  leftDrive(-1.2, 40, true);
  wait(200, msec);

  encoderDrive(2.6, 60, true);
  wait(500, msec);
  brakeIntakes();
  spinIntakes(false, 40);
  wait(600, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
}

void redProtecAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);

  spinIntakes(true, 100);
  encoderDrive(1, 100, true);
  encoderDrive(-1, 100, true);
  brakeDrive();
  wait(100, msec);

  encoderDrive(1.95, 45, true);
  brakeDrive();
  wait(100, msec);

  rightDrive(-1.3, 40, false);
  leftDrive(1.3, 40, true);
  wait(200, msec);

  encoderDrive(0.7, 45, true);
  wait(100, msec);

  rightDrive(-0.2, 40, true);
  encoderDrive(-3, 80, true);
  wait(100, msec);

  rightDrive(-1.2, 40, false);
  leftDrive(1.2, 40, true);
  wait(200, msec);

  encoderDrive(2.6, 60, true);
  wait(500, msec);
  brakeIntakes();
  spinIntakes(false, 40);
  wait(600, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();

}

void blueUnProtecAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  encoderDrive(1.2, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);

  spinIntakes(true, 100);
  encoderDrive(1, 100, true);
  brakeDrive();
  wait(200, msec);
  encoderDrive(-0.1, 100, true);
  encoderDrive(1, 100, true);
  brakeDrive();
  wait(200, msec);
  encoderDrive(-0.1, 100, true);
  encoderDrive(1, 100, true);
  brakeDrive();
  wait(200, msec);
  encoderDrive(-0.1, 100, true);
  encoderDrive(1, 100, true);
  brakeDrive();
  wait(200, msec);
  encoderDrive(-0.1, 100, true);
  encoderDrive(1, 100, true);
  brakeDrive();
  wait(200, msec);
  encoderDrive(1, 100, true);
  encoderDrive(-0.1, 100, true);
  brakeDrive();
  wait(500, msec);
  brakeIntakes();

  encoderDrive(-2.8, 80, true);
  wait(100, msec);
  leftDrive(-1.6, 40, false);
  rightDrive(1.6, 40, true);
  wait(200, msec);

  encoderDrive(1.7, 60, true);
  spinIntakes(false, 40);
  wait(450, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  encoderDrive(0.2, 20, true);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
  
}

void redUnProtecAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  encoderDrive(1.2, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.5, 50, true);

  spinIntakes(true, 100);
  encoderDrive(4, 30, true);
  brakeDrive();
  wait(500, msec);
  brakeIntakes();

  encoderDrive(-3, 80, true);
  wait(100, msec);
  leftDrive(1.6, 40, false);
  rightDrive(-1.6, 40, true);
  wait(200, msec);

  encoderDrive(1.52, 60, true);
  spinIntakes(false, 40);
  wait(450, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
  
}

