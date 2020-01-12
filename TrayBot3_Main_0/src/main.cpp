/*
62B TrayBot 3.0 Main
No Auton
1/11/20

Controls:
Tank drive
L1 - Tray In
L2 - Tray Out
R1 - Intake in
R2 - Intake Out
Up - Arm up
Down - Arm down
Left - Tower high
Right - Tower low
X - Stack
B - Stop all functions
*/


#include "vex.h"

using namespace vex;


vex::brain Brain;

vex::competition Competition;

vex::controller Controller;

vex::motor LeftMotor1 = vex::motor( vex::PORT1 );
vex::motor LeftMotor2 = vex::motor( vex::PORT2 );
vex::motor RightMotor1 = vex::motor( vex::PORT9, true );
vex::motor RightMotor2 = vex::motor( vex::PORT10, true );
vex::motor TrayMotor = vex::motor( vex::PORT5 );
vex::motor ArmMotor = vex::motor( vex::PORT6, true );
vex::motor RightIntakeMotor = vex::motor( vex::PORT8, true );
vex::motor LeftIntakeMotor = vex::motor( vex::PORT7 );


int traySpeedPCT = 100;
int intakeSpeedPCT = 80;
int armSpeedPCT = 80;
int isFunc = 0;


void towerLow() {
  isFunc = 1;
  TrayMotor.startSpinFor(vex::directionType::fwd, 2.4, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  wait(250, timeUnits::msec);
  ArmMotor.spinFor(vex::directionType::rev, 2.3, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  isFunc = 0;
}

void towerHigh() {
  isFunc = 1;
  TrayMotor.startSpinFor(vex::directionType::fwd, 2.7, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  wait(350, timeUnits::msec);
  ArmMotor.spinFor(vex::directionType::rev, 3.2, vex::rotationUnits::rev, 90, vex::velocityUnits::pct);
  isFunc = 0;
}

void stack() {
  isFunc = 1;
  RightIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT/40, vex::velocityUnits::pct);
  LeftIntakeMotor.spin(vex::directionType::rev, intakeSpeedPCT/40, vex::velocityUnits::pct);
  TrayMotor.spinFor(vex::directionType::fwd, 10.5, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
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
  

// Pre-Auton
void pre_auton( void ) {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
}


// Auton
void autonomous( void ) {
  
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


int main() {
    pre_auton();

    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
                     
    while(1) {
      vex::task::sleep(20);
    }    
       
}