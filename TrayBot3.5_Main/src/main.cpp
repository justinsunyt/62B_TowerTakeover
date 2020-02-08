/*
62B TrayBot 3.5 Main
No Auton
1/28/20

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
  Inertial.calibrate();
}


// Auton
void autonomous( void ) {
  
}


int main() {
    Competition.autonomous( RPAuton );
    Competition.drivercontrol( usercontrol );
    
    pre_auton();

    while(1) {
      vex::task::sleep(100);
    }    
       
}