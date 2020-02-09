#pragma once
#include "vex.h"
#include "config.h"

using namespace vex;


int traySpeedPCT = 100;
int intakeSpeedPCT = 80;
int armSpeedPCT = 80;
int isFunc = 0;


//Functions
void towerLow() {
  isFunc = 1;
  TrayMotor.startSpinFor(vex::directionType::fwd, 3.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  wait(400, timeUnits::msec); 
  ArmMotor.spinFor(vex::directionType::rev, 2.7, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  isFunc = 0;
}

void towerHigh() { 
  isFunc = 1;
  TrayMotor.startSpinFor(vex::directionType::fwd, 3.9, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  wait(400, timeUnits::msec);
  ArmMotor.spinFor(vex::directionType::rev, 3.6, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  isFunc = 0;
}

void stack() {
  isFunc = 1;
  RightIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT/40, vex::velocityUnits::pct);
  LeftIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT/40, vex::velocityUnits::pct);
  TrayMotor.spinFor(vex::directionType::fwd, 9.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  RightIntakeMotor.stop(brakeType::brake);
  LeftIntakeMotor.stop(brakeType::brake);
  isFunc = 0;
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
  isFunc = 1;
  spinIntakes(true, 100);
  TrayMotor.startSpinFor(directionType::fwd, 1, rotationUnits::rev, 100, velocityUnits::pct);
  ArmMotor.spinFor(directionType::rev, 1.1, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  
  brakeIntakes();
  
  TrayMotor.startSpinFor(directionType::rev, 1, rotationUnits::rev, 100, velocityUnits::pct);
  ArmMotor.spinFor(directionType::fwd, 1.15, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  isFunc = 0;
}

void driveMotors()
{
  while (1) {
    LeftMotor1.spin(vex::directionType::fwd, Controller.Axis3.position(), vex::velocityUnits::pct);
    LeftMotor2.spin(vex::directionType::fwd, Controller.Axis3.position(), vex::velocityUnits::pct);
    RightMotor1.spin(vex::directionType::fwd, Controller.Axis2.position(), vex::velocityUnits::pct);
    RightMotor2.spin(vex::directionType::fwd, Controller.Axis2.position(), vex::velocityUnits::pct);
    vex::task::sleep(5);
  }
}

void armTrayIntakeMotors()
{
  while (1) {
    if(Controller.ButtonL1.pressing()) {
      if(isFunc == 0){
        TrayMotor.spin(vex::directionType::rev, traySpeedPCT, vex::velocityUnits::pct);
      }
    }
      
    else 
    if(Controller.ButtonL2.pressing()) { 
      if(isFunc == 0){
        TrayMotor.spin(vex::directionType::fwd, traySpeedPCT, vex::velocityUnits::pct);
      }
    }
    
    else
    if(Controller.ButtonX.pressing()) {
      if(isFunc == 0){
        stack();
      }
    }

    else
    if(Controller.ButtonY.pressing()) {
      if(isFunc == 0){
        deploy();
      }
    }
    
    else {
      TrayMotor.stop(vex::brakeType::brake);
      RightIntakeMotor.stop(vex::brakeType::hold);
      LeftIntakeMotor.stop(vex::brakeType::hold);
    }


    if(Controller.ButtonR1.pressing()) { 
      RightIntakeMotor.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
      LeftIntakeMotor.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
    }
      
    else 
    if(Controller.ButtonR2.pressing()) { 
      RightIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT, vex::velocityUnits::pct);
      LeftIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT, vex::velocityUnits::pct);
    }
    
    else {
      RightIntakeMotor.stop(vex::brakeType::hold);
      LeftIntakeMotor.stop(vex::brakeType::hold);
    }


    if(Controller.ButtonRight.pressing()) {
      if(isFunc == 0){
        towerLow();
      }
    }
    
    else if(Controller.ButtonLeft.pressing()) {
      if(isFunc == 0){
        towerHigh();
      }
    }

    else 
    if(Controller.ButtonDown.pressing()) { 
      if(isFunc == 0){
        ArmMotor.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
      }
    }
    
    else 
    if(Controller.ButtonUp.pressing()) {
      if(isFunc == 0){
        ArmMotor.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      }
    }

    else {
      ArmMotor.stop(vex::brakeType::hold);
    }

    vex::task::sleep(5);
  }
}


//User Control
void usercontrol( void ) {
  TrayMotor.resetPosition();
  ArmMotor.resetPosition();
  vex::thread driveTask(driveMotors);
  vex::thread armTrayIntakeTask(armTrayIntakeMotors);


  while (1) {
    if(Controller.ButtonB.pressing()) {
      armTrayIntakeTask.interrupt();
      ArmMotor.stop();
      TrayMotor.stop();
      isFunc = 0;
      vex::thread armTrayIntakeTask(armTrayIntakeMotors);
    }

    vex::task::sleep(20);
  }
}