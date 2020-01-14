#include "vex.h"
#include "config.h"

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
  ArmMotor.spinFor(directionType::fwd, 1.1, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
}

void onePointAuton() {
  encoderDrive(3, 80, true);
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
  wait(500, msec);
  deploy();
  
  spinIntakes(true, 80);
  encoderDrive(4, 50, true);
  brakeIntakes();

  encoderDrive(3, 80, true);
}
