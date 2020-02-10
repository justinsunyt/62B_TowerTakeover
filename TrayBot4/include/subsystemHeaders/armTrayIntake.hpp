#include "main.h"

//HELPER FUNCTIONS
void setArm(int power);
void setIntake(int left, int right);
void setTray(int power);

//MACROS
void stack();
void towerLow();
void towerHigh();

//DRIVER CONTROL FUNCTIONS
void setArmMotor();
void setIntakeMotors();
void setTrayMotor();

void setArmTrayIntakeMotors(void* param);
