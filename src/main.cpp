#include "main.h"
#include "Functions.h"
#include "PIDControls.h"
#include "MotorInit.h"
#include "auton.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	Arm.tare_position();
	intake.tare_position();
	bool mode = false;
	bool mode2 = true;
	bool mode3 = true;
}

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
void autonomous() {
	Arm.tare_position();
	intake.tare_position();
	bool mode = false;
	bool mode2 = true;
	bool mode3 = true;
	moveBack(40.87,0.2,0.3,0.2);
	pros::delay(1000);
	clampDown();
	pros::delay(50);
	RunIntake(212);
	pros::delay(50);
	turn(60,3,1.0,0.5,1,1);
	pros::delay(50);
	move(42,0.1,0.25,0.2);
	pros::delay(50);
	turn(-154,3,1.0,0.5,9,9);
	pros::delay(50);
	move(51.94,0.2,0.5,0.2);
	pros::delay(50);
	turn(116,3,1,0.5,1,1);
	pros::delay(50);
	move(48,0.2,0.25,0.2);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
Arm.tare_position();
	intake.tare_position();
	bool mode = false;
	bool mode2 = true;
	bool mode3 = true;
while(true){
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
			if(mode == true){
				clamper.set_value(1);
				mode = false;
				pros::delay(10);
				pros::lcd::print(0, "mode = false");
			}
			else{
				clamper.set_value(0);
				mode = true;
				pros::delay(10);
				pros::lcd::print(0, "mode = true");
			}
		}
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			intake.move_velocity(50);
		}else{
			intake.move_velocity(0);
		}
		driveFunc(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    	moveIntake();
		moveArm();
		sigmaFlipOut185();
		slowIntake();
	    pros::delay(10);
   }
   //clamper.set_value(1);
   //pros::delay(1000);
   //turn(90);
   //PIDArm();  
   //}*/
}
