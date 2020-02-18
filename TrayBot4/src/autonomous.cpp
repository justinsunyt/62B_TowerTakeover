#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
  .withMotors({1, 2}, {10, 9})
  .withDimensions(AbstractMotor::gearset::green, {{2.75_in, 11.2_in}, imev5GreenTPR})
  .withMaxVelocity(MOVEVELOCITY)
  .build();


void oneP() {
  chassis->moveDistance(1_ft);
  chassis->moveDistance(-1_ft);
}

void skills() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(0.8_ft);
  pros::delay(1000);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);
}

void RP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(0.8_ft);
  pros::delay(1000);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);
}

void BP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(0.8_ft);
  pros::delay(1000);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);
}

void RUP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(0.8_ft);
  pros::delay(1000);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);

  setIntake(127);
  chassis->moveDistance(2_ft);
  pros::delay(200);
  setIntake(0);
  chassis->moveDistance(-1_ft);

  chassis->setMaxVelocity(TURNVELOCITY);
  chassis->turnAngle(-50_deg);
  chassis->setMaxVelocity(MOVEVELOCITY);
  chassis->moveDistance(-1.8_ft);
  chassis->setMaxVelocity(TURNVELOCITY);
  chassis->turnAngle(50_deg);

  chassis->setMaxVelocity(MOVEVELOCITY);
  setIntake(127);
  chassis->moveDistance(3_ft);
  pros::delay(200);
  setIntake(0);
  chassis->moveDistance(-1_ft);

  chassis->setMaxVelocity(TURNVELOCITY);
  chassis->turnAngle(135_deg);

  chassis->moveDistance(1.5_ft);
  setIntake(-50);
  pros::delay(300);
  setIntake(0);
  stack();
  pros::delay(300);
  chassis->moveDistance(-1_ft);

}

void BUP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(0.8_ft);
  pros::delay(1000);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);
}

void autonomous() {
  if (auton == 0) {
    // oneP();
    RUP();
  }
  else if (auton == 1) {
    skills();
  }
  else if (auton == 2) {
    RP();
  }
  else if (auton == 3) {
    BP();
  }
  else if (auton == 4) {
    RUP();
  }
  else if (auton == 5) {
    BUP();
  }
}
