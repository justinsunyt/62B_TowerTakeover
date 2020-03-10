#include "main.h"
#include "okapi/impl/util/configurableTimeUtilFactory.hpp"

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

ConfigurableTimeUtilFactory *pTimeUtilFactory = new ConfigurableTimeUtilFactory(500, 100, 20_ms);
TimeUtilFactory factory = (TimeUtilFactory) *pTimeUtilFactory;
std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
  .withMotors({1, 2}, {4, 3})
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.8_in}, imev5GreenTPR})
  .withChassisControllerTimeUtilFactory(factory)
  .withGains(
        {0.0062, 0.0000008, 0.00023}, // Distance controller gains
        {0.0045, 0, 0.0001}, // Turn controller gains
        {0.0015, 0, 0}  // Angle controller gains
    )
  .withMaxVelocity(MOVE)
  .build();


void testAuton() {
  chassis->moveDistance(3_ft);
  chassis->turnAngle(360_deg);
  chassis->moveDistance(-3_ft);
}

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
  pros::delay(800);
  deploy();
  chassis->waitUntilSettled();
  chassis->moveDistanceAsync(-0.5_ft);
  pros::delay(400);
}

void RUP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->setMaxVelocity(SLOWMOVE);
  chassis->moveDistanceAsync(2.7_ft);
  pros::delay(250);
  deploy();
  chassis->setMaxVelocity(INTAKEMOVE);
  setArm(-5);
  setIntake(127);
  chassis->waitUntilSettled();
  pros::delay(200);
  resetArmTray();
  setIntake(0);
  setArm(0);
  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(-1_ft);

  chassis->setMaxVelocity(TURN);
  chassis->turnAngle(-60_deg);
  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(-2.1_ft);
  chassis->setMaxVelocity(TURN);
  chassis->turnAngle(60_deg);

  chassis->setMaxVelocity(INTAKEMOVE);
  setIntake(127);
  setArm(-5);
  chassis->moveDistance(3.3_ft);
  pros::delay(200);
  resetArmTray();
  setIntake(0);
  setArm(0);
  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(-2.3_ft);
  setIntake(-80);
  pros::delay(350);
  setIntake(0);

  chassis->setMaxVelocity(TURN);
  chassis->turnAngle(135_deg);

  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(1.7_ft);
  fastStack();
  setTray(0);
  pros::delay(400);
  chassis->setMaxVelocity(SLOWMOVE);
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
  arm.tare_position();
  tray.tare_position();
  arm.set_brake_mode(MOTOR_BRAKE_HOLD);
  tray.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
  intakeRight.set_brake_mode(MOTOR_BRAKE_HOLD);

  if (auton == 0) {
    //testAuton();
    //oneP();
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
