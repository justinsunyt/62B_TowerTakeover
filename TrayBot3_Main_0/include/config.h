#pragma once


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