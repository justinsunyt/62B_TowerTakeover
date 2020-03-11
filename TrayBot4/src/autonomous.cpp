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

ConfigurableTimeUtilFactory timeUtilFactory = ConfigurableTimeUtilFactory(500, 100, 20_ms);
// TimeUtilFactory factory = (TimeUtilFactory) timeUtilFactory;
std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
  .withMotors({1, 2}, {4, 3})
  .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.8_in}, imev5GreenTPR})
  .withChassisControllerTimeUtilFactory(timeUtilFactory)
  .withGains(
        {0.0062, 0.0000008, 0.00023}, // Distance controller gains
        {0.0045, 0, 0.0001}, // Turn controller gains
        {0.0015, 0, 0}  // Angle controller gains
    )
  .withMaxVelocity(MOVE)
  .build();

//FUNCTIONS
void imuTurn(double degrees, double kP, double kI, double kD, bool dir, double speedPCT = 100) {
  double rotation;
  double error;
  double integral;
  double derivative;
  double speed;
  double prevError;
  double done = 0;

  rotation = inertial.get_rotation();

  if (dir) {
    while(done < 1) {
      error = degrees - (inertial.get_rotation() - rotation);
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

      setDrive(speed, -speed);

      pros::delay(10);

      if (error < 0.8 && error > -0.8) {
        done += 0.1;
      }
    }
  } else {
    while(done < 1) {
      error = degrees + (inertial.get_rotation() - rotation);
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

      setDrive(-speed, speed);

      pros::delay(10);

      if (error < 0.8 && error > -0.8) {
        done += 0.1;
      }
    }
  }
}


//AUTONS
void testAuton() {
  chassis->moveDistance(3_ft);
  imuTurn(180, 1.5, 0, 5, true, TURN);
  imuTurn(180, 1.5, 0, 5, false, TURN);
  chassis->moveDistance(-3_ft);
}

void oneP() {
  chassis->moveDistance(1_ft);
  chassis->moveDistance(-1_ft);
}

void skills() {

}

void RP() {

}

void BP() {

}

void RUP() {
  chassis->stop();
  chassis->waitUntilSettled();
  chassis->setMaxVelocity(SLOWMOVE);
  chassis->moveDistanceAsync(0.5_ft);
  pros::delay(300);
  holdDrive();
  deploy();

  coastDrive();
  chassis->setMaxVelocity(INTAKEMOVE);
  setArm(-5);
  setIntake(127);
  chassis->moveDistance(2.5_ft);
  pros::delay(200);
  setArm(0);

  imuTurn(35, 1.5, 0, 5, false, TURN);
  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(-2_ft);
  imuTurn(35, 1.5, 0, 5, true, TURN);

  chassis->setMaxVelocity(INTAKEMOVE);
  setArm(-5);
  setIntake(127);
  chassis->moveDistance(3.5_ft);
  pros::delay(200);
  setIntake(0);
  setArm(0);

  chassis->setMaxVelocity(MOVE);
  chassis->moveDistance(-2.5_ft);
  setIntake(-60);
  pros::delay(300);
  setIntake(0);

  imuTurn(135, 1.5, 0, 5, true, TURN);

  chassis->setMaxVelocity(MOVE);
  chassis->moveDistanceAsync(1.7_ft);
  pros::delay(800);
  fastStack();
  setTray(0);
  chassis->setMaxVelocity(SLOWMOVE);
  chassis->moveDistance(0.1_ft);

  chassis->setMaxVelocity(MOVE);
  chassis->moveDistanceAsync(-1_ft);
  pros::delay(500);
  resetArmTray();
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
