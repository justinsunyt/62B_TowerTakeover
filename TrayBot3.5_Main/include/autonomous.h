#include "vex.h"
#include "config.h"
#include "usercontrol.h"

using namespace vex;


//Functions
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

void pidTurn(float degrees, float kP, float kI, float kD, bool dir) {
  Inertial.resetRotation();
  float error;
  float integral;
  float derivative;
  float speed;
  float prevError;
  float done = 0;

  if (dir) {
    while(done < 1) {
      error = degrees - Inertial.rotation();
      integral = integral + error;
      if (error == 0 or error > degrees) {
        integral = 0;
      }
      if (error > 360) {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      speed = error*kP + integral*kI + derivative*kD;

      LeftMotor1.spin(directionType::fwd, speed, velocityUnits::pct);
      LeftMotor2.spin(directionType::fwd, speed, velocityUnits::pct);
      RightMotor1.spin(directionType::rev, speed, velocityUnits::pct);
      RightMotor2.spin(directionType::rev, speed, velocityUnits::pct);  

      wait(15, msec);

      if (error < 0.8 && error > -0.8) {
        done += 0.1;
      }
    }

  } else {
    while(done < 1) {
      error = degrees + Inertial.rotation();
      integral = integral + error;
      if (error == 0 or error > degrees) {
        integral = 0;
      }
      if (error > 360) {
        integral = 0;
      }
      derivative = error - prevError;
      prevError = error;
      speed = error*kP + integral*kI + derivative*kD;

      LeftMotor1.spin(directionType::rev, speed, velocityUnits::pct);
      LeftMotor2.spin(directionType::rev, speed, velocityUnits::pct);
      RightMotor1.spin(directionType::fwd, speed, velocityUnits::pct);
      RightMotor2.spin(directionType::fwd, speed, velocityUnits::pct);  

      wait(15, msec);

      if (error < 1.3 && error > -1.3) {
        done += 0.15;
      }
    } 
  }
  brakeDrive();
}


//Autons

//One Point
void onePointAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(2, 80, true);
  encoderDrive(-3, 80, true);
  brakeDrive();
}

//PID Turn Test
void testAuton() {
  while(Inertial.isCalibrating()){
    wait(1, msec);
  }

  pidTurn(90, 1.5, 0, 5, true);
  Controller.Screen.print("Done");
}

//Red UnProtected (5pt)
void RUPAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  encoderDrive(1.5, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.8, 60, true);

  spinIntakes(true, 100);
  encoderDrive(4, 36, true);
  brakeDrive();
  wait(500, msec);
  brakeIntakes();

  encoderDrive(-2.1, 80, true);
  wait(100, msec);
  pidTurn(130, 1.5, 0, 5, true);
  wait(200, msec);

  encoderDrive(1.58, 60, true);
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

//Blue UnProtected (5pt)
void BUPAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  encoderDrive(1.5, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.8, 60, true);

  spinIntakes(true, 100);
  encoderDrive(4, 36, true);
  brakeDrive();
  wait(500, msec);
  brakeIntakes();

  encoderDrive(-2.1, 80, true);
  wait(100, msec);
  pidTurn(130, 1.5, 0, 5, false);
  wait(200, msec);

  encoderDrive(1.58, 60, true);
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

//Skills - Start on Red UnProtected (9pt)
void skillsAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  encoderDrive(1.5, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-0.8, 60, true);

  spinIntakes(true, 100);
  encoderDrive(4, 36, true);
  brakeDrive();
  wait(1000, msec);
  brakeIntakes();

  encoderDrive(-1.1, 80, true);
  wait(100, msec);
  pidTurn(47, 1.5, 0, 5, false);
  wait(200, msec);

  encoderDrive(-3.5, 50, true);
  wait(100, msec);
  pidTurn(47, 1.5, 0, 5, true);
  wait(200, msec);
  encoderDrive(-0.4, 60, true);
  wait(100, msec);

  spinIntakes(true, 100);
  encoderDrive(5.5, 36, true);
  brakeDrive();
  wait(1500, msec);
  brakeIntakes();

  encoderDrive(-3.4, 80, true);
  wait(100, msec);
  pidTurn(130, 1.5, 0, 5, true);
  wait(200, msec);

  encoderDrive(1.56, 60, true);
  spinIntakes(false, 40);
  wait(350, msec);
  brakeIntakes();
  wait(100, msec);
  stack();
  wait(200, msec);
  encoderDrive(0.2, 15, true);
  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(300, msec);
  encoderDrive(-1, 60, true);
  TrayMotor.stop();
  
  encoderDrive(-1, 60, true);
  pidTurn(140, 1.5, 0, 5, true);
  wait(100, msec);

  encoderDrive(-1.5, 50, true);

  TrayMotor.spin(directionType::rev, 100, velocityUnits::pct);
  wait(2300, msec);
  TrayMotor.stop();

  spinIntakes(true, 100);
  encoderDrive(6, 50, true);
  brakeIntakes();

  encoderDrive(-1, 60, true);

  spinIntakes(false, 40);
  wait(350, msec);
  brakeIntakes();

  towerHigh();
  
  encoderDrive(1.2, 50, true);
  spinIntakes(false, 60);
  wait(1000, msec);
  brakeIntakes();

}