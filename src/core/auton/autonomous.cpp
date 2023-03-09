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

void drivetrainMove(int voltage, int time) {
	// Drive forward based on voltage
	frontLeft.move_voltage(voltage);
	backLeft.move_voltage(voltage);
	frontRight.move_voltage(voltage);
	backRight.move_voltage(voltage);

	pros::delay(time);
	
	frontLeft.brake();
	backLeft.brake();
	frontRight.brake();
	backRight.brake();
}

void drivetrainTurn(int dir, int time) {
	frontLeft.move_voltage(-6000 * dir);
	backLeft.move_voltage(-6000 * dir);
	frontRight.move_voltage(6000 * dir);
	backRight.move_voltage(6000 * dir);

	pros::delay(time);
	
	frontLeft.brake();
	backLeft.brake();
	frontRight.brake();
	backRight.brake();
}

void rollerAuton() {
	roller.move_voltage(-5000);

	drivetrainMove(6000, 1000);
    roller.brake();

	drivetrainMove(-3000, 1000);
}

void dispenseDiscs() {
	// Dispense discs
	intake.move_voltage(-12000);
	pros::delay(6000);
	intake.brake();
}

void autonomous() {
    switch (autonSelection) {
		case RED_1: // Within auton starting line, facing rollers
			// Move forward, spin rollers, move back
			rollerAuton();

			// Turn left 90 deg
			drivetrainTurn(-1, 690);
			// Drive into low goal
			drivetrainMove(4000, 4000);

			// Dispense discs
			dispenseDiscs();
			break;
		case RED_2: // Outside auton starting line
			// Navigate from starting line to roller
            drivetrainMove(3000, 2100);
			drivetrainTurn(1, 2000);
			drivetrainMove(2000, 2000);

			// Spin rollers
			rollerAuton();

			// Turn and drive into low goal
			drivetrainMove(-2000, 500);
			drivetrainTurn(1, 2000);
			drivetrainMove(4000, 3200);

			// Dispense discs
			dispenseDiscs();
			break;
		case RED_3:
			// Pure roller auton only
			rollerAuton();
			break;
		case RED_4:
			// Pure low goal dispense only
			drivetrainMove(6000, 1000);

			intake.move_voltage(-12000);
			pros::delay(6000);
			intake.brake();
			break;

		// Unused blue autons
		case RED_5:
			break;
		case BLUE_1:
			break;
		case BLUE_2:
			break;
		case BLUE_3:
			break;
		case BLUE_4:
			break;
		case BLUE_5:
			break;
			
		case SKILLS:
			roller.move_voltage(-5000);

			drivetrainMove(8000, 1000);
    		roller.brake();

			drivetrainMove(-3000, 1000);

			expansion.move_voltage(12000);
			pros::delay(2000);
			expansion.brake();
			break;
	}
}

//void autonomous() {
//	roller.move_voltage(-5000);
//
//	frontLeft.move_voltage(6000);
//	backLeft.move_voltage(6000);
//	frontRight.move_voltage(6000);
//	backRight.move_voltage(6000);
//
//	pros::delay(500);
//
//	roller.brake();
//
//	frontLeft.move_voltage(-3000);
//	backLeft.move_voltage(-3000);
//	frontRight.move_voltage(-3000);
//	backRight.move_voltage(-3000);
//	
//	pros::delay(1000);
//
//	frontLeft.brake();
//	backLeft.brake();
//	frontRight.brake();
//	backRight.brake();
//}