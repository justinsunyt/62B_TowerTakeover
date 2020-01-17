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
  ArmMotor.spinFor(directionType::fwd, 1.3, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
}

void onePointAuton() {
  encoderDrive(2, 80, true);
  encoderDrive(-3, 80, true);
  brakeDrive();
}

void blueProtecAuton() {
  encoderDrive(3, 80, false);
  wait(500, msec);
  deploy();
  spinIntakes(true, 80);
}

void blueUnProtecAuton() {
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.5, 60, true);

  spinIntakes(true, 100);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1.5, 45, true);
  brakeDrive();
  wait(400, msec);
  brakeIntakes();

  encoderDrive(-3.5, 80, true);
  wait(100, msec);
  leftDrive(-1.6, 40, false);
  rightDrive(1.6, 40, true);
  wait(200, msec);

  encoderDrive(1.5, 60, true);
  spinIntakes(false, 40);
  wait(350, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
  
}

void redUnProtecAuton() {
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.5, 60, true);

  spinIntakes(true, 100);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1, 45, true);
  brakeDrive();
  wait(50, msec);
  encoderDrive(1.5, 45, true);
  brakeDrive();
  wait(400, msec);
  brakeIntakes();

  encoderDrive(-3.5, 80, true);
  wait(100, msec);
  leftDrive(1.6, 40, false);
  rightDrive(-1.6, 40, true);
  wait(200, msec);

  encoderDrive(1.5, 60, true);
  spinIntakes(false, 40);
  wait(350, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(100, msec);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
  
}
