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
#include "config.h"
#include "usercontrol.h"
#include "autonomous.h"

using namespace vex;
  

// Pre-Auton
void pre_auton( void ) {
  ArmMotor.setBrake(vex::brakeType::hold);
  RightIntakeMotor.setBrake(vex::brakeType::hold);
  LeftIntakeMotor.setBrake(vex::brakeType::hold);
  TrayMotor.setBrake(vex::brakeType::brake);
}


// Auton
void autonomous( void ) {
  
}


int main() {
    pre_auton();

    Competition.autonomous( blueUnProtecAuton );
    Competition.drivercontrol( usercontrol );
                     
    while(1) {
      vex::task::sleep(20);
    }    
       
}