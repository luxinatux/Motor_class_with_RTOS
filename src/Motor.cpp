/** @file Motor.cpp
 *    This file contains a creation of a motor class and its functions.
 * 	  The goal of the functions are to create a motor instance and send
 * 	  a PWM signal of the correct size. 
 *  
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */

#include <Arduino.h>
#include <Motor.h>
#include <Servo.h>

/** @brief   Constructor of the motor
 *  @details This is a function that creates a servo instance of the motor
 * 			 on startup. 
 *  @param   sir The name of the Servo instance created
 */
Motor::Motor(void)
{
	Servo sir;
	// sir.writeMicroseconds(1500);
	// delay(7000);
}
/** @brief   Initializing the motors to the motor specifications
 *  @details This function was created to attach pins and accept 
 * 			 various motor parameters that will be implemented into
 * 			 the motor class. It is an assignment function
 *  @param   in_pin The location of the PWM signal for a specific motor
 *  @param fwd_sig The largest value of the forward PWM signal in ms
 *  @param Reverse The smallest value of the Reverse PWM signal in ms
 *  @param stop the value of no motor movement in ms
 */
void Motor::initialize(byte in_pin, uint16_t fwd_sig, uint16_t Reverse, uint16_t stop)
 {
	sir.attach(in_pin);
	sir.writeMicroseconds(1500);
	delay(7000);	
    SERVO_PIN = in_pin;
    FWD_SIG = fwd_sig;
    REV_SIG = Reverse;
    STOP_SIG = stop;

}
/** @brief   Update motor to the correct PWM signal based on user input of throttle
 *  @details This function updates the PWM duty cycle based on motor specifications
 * 			 and values incorportated in the class
 *  @param  throttle A value -100 to 100 that corresponds the %
 * 					 of max speed in each direction
 *  @param finalmicro The final ms PWM signal sent to motor to be updated
 */
void Motor::updateMotor(float throttle)
{
	uint16_t finalmicro = 0;
	
    if( throttle < -100 ) 
    {
 			throttle = -100; // making sure the throttle signal is in correct range
			finalmicro = REV_SIG;
 	}	
    else if( throttle > 100) 
    {
 			throttle = 100;	// making sure the throttle signal is in correct range
			finalmicro = FWD_SIG;
 	}
	else if( throttle > 0) 
    {
			
			finalmicro = ((FWD_SIG - STOP_SIG)*(throttle/100) + STOP_SIG); //calculation of PWM for positive throttle
 	}
	else if( throttle < 0) 
    {
			
			finalmicro = (( STOP_SIG - REV_SIG)*(throttle/100) + REV_SIG);//calculation of PWM for negative throttle
			
 	}
	 else if( throttle = 0) 
    {
			
			finalmicro = STOP_SIG; // Zero throttle
 	}	
    else  
    {
 			printf("Houston	we have a problem");
 	}

 	//printf("The duty cycle is: %d\n", throttle_Sig);

	sir.writeMicroseconds(finalmicro); // update motor with finalmicro PWM 
	Serial.print(finalmicro);
	// -100 corresponds to 1100 and 100 corresponds to 1900
	// I need to scale the values from -100 and 100 to the range of 1100 to 1900
	
	return;
}