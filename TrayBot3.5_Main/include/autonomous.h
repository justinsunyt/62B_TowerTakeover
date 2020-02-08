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

void pidTurn(float degrees, float kP, float kI, float kD, bool dir, float speedPCT = 100) {
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
      speed = speedPCT/100 * error*kP + integral*kI + derivative*kD;

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
      speed = speedPCT/100 * error*kP + integral*kI + derivative*kD;

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

  pidTurn(130, 1.5, 0, 5, true, 80);
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

//Red Protected (4pt)
void RPAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(1000, msec);

  spinIntakes(true, 100);
  encoderDrive(2.6, 45, true);
  brakeDrive();
  wait(100, msec);

  rightDrive(-1.3, 40, false);
  leftDrive(1.3, 40, true);
  wait(200, msec);

  encoderDrive(0.75, 45, true);
  wait(100, msec);

  rightDrive(-0.32, 40, true);
  encoderDrive(-2.8, 80, true);
  wait(100, msec);

  rightDrive(-1.2, 40, false);
  leftDrive(1.2, 40, true);
  wait(100, msec);

  encoderDrive(3, 60, true);
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

//Blue Protected (4pt)
void BPAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
  encoderDrive(1, 80, false);
  wait(100, msec);
  deploy();
  wait(1000, msec);

  spinIntakes(true, 100);
  encoderDrive(2.5, 45, true);
  brakeDrive();
  wait(100, msec);

  rightDrive(1.25, 40, false);
  leftDrive(-1.25, 40, true);
  wait(200, msec);

  encoderDrive(0.75, 45, true);
  wait(100, msec);

  leftDrive(-0.32, 40, true);
  encoderDrive(-2.6, 80, true);
  wait(100, msec);

  rightDrive(1.2, 40, false);
  leftDrive(-1.2, 40, true);
  wait(100, msec);

  encoderDrive(2.95, 60, true);
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

//Skills - Start on Red UnProtected (24pt)
void skillsAuton() {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);

  //deploy
  encoderDrive(1.5, 80, false);
  wait(100, msec);
  deploy();
  wait(500, msec);
  encoderDrive(-1, 80, true);
  wait(200, msec);

  //intake first row of cubes
  spinIntakes(true, 100);
  encoderDrive(4, 36, true);
  brakeDrive();
  wait(1000, msec);
  brakeIntakes();

  //turn to second row of cubes
  encoderDrive(-1.1, 80, true);
  wait(100, msec);
  pidTurn(47, 1.5, 0, 5, false);
  wait(200, msec);
  encoderDrive(-3.5, 50, true);
  wait(100, msec);
  pidTurn(47, 1.5, 0, 5, true);
  wait(200, msec);
  encoderDrive(-0.8, 60, true);
  wait(100, msec);

  //intake second row of cubes
  spinIntakes(true, 100);
  encoderDrive(4.55, 36, true);
  brakeDrive();
  wait(1500, msec);
  brakeIntakes();

  //back up and turn to goalzone
  encoderDrive(-2.5, 80, true);
  wait(500, msec);
  pidTurn(130, 1.5, 0, 5, true, 80);
  wait(200, msec);

  //stack in goalzone
  encoderDrive(1.4, 60, true);
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
  
  //back out and turn to face tower
  encoderDrive(-1, 60, true);
  pidTurn(140, 1.5, 0, 5, true);
  wait(100, msec);

  //reset tray
  encoderDrive(-2, 80, false);
  TrayMotor.startSpinFor(vex::directionType::rev, 8.6, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  wait(2000, msec);

  //intake cube under tower
  spinIntakes(true, 100);
  encoderDrive(6, 50, true);
  brakeIntakes();

  //back up and slightly outake cube
  encoderDrive(-1, 60, true);
  spinIntakes(false, 40);
  wait(500, msec);
  brakeIntakes();
  
  //stack cube in tower
  towerHigh();
  encoderDrive(1.2, 50, true);
  spinIntakes(false, 60);
  wait(1000, msec);
  brakeIntakes();
  
  //back up and reset arms and tray
  encoderDrive(-1, 50, false);
  wait(100, msec);
  ArmMotor.startSpinFor(vex::directionType::fwd, 3.6, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  wait(300, msec);
  TrayMotor.startSpinFor(vex::directionType::rev, 4.2, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);

  //back up and turn to face tower
  encoderDrive(-2, 60, true);
  pidTurn(90, 1.5, 0, 5, true);

  //intake cube under tower
  spinIntakes(true, 100);
  encoderDrive(5, 50, true);
  brakeIntakes();

  //back up and slightly outake cube
  encoderDrive(-1, 60, true);
  spinIntakes(false, 40);
  wait(500, msec);
  brakeIntakes();

  //stack cube in tower
  towerLow();
  spinIntakes(false, 60);
  wait(1000, msec);
  brakeIntakes();

  //back up
  encoderDrive(-1, 50, true);
}