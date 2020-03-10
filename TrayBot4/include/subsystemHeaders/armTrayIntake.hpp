#include "main.h"

//HELPER FUNCTIONS
void setArm(int power);
void setIntake(int power);
void setTray(int power);

//MACROS
void stack();
void fastStack();
void towerLow();
void towerHigh();
void resetArmTray();
void deploy();

//DRIVER CONTROL FUNCTIONS
void setArmMotor();
void setIntakeMotors();
void setTrayMotor();

void setArmTrayIntakeMotors(void* param);
