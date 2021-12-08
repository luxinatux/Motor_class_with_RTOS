/** @file main.cpp
 *    This file contains a simple demonstration program for ME507 which uses
 *    FreeRTOS to do multitasking. One of the tasks makes a square wave which
 *    can be viewed and measured with a signal analyzer or oscilloscope, while
 *    other tasks just print fairly useless things to the serial port. 
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */

#include <Arduino.h>
#include <Motor.h>
#include <Servo.h>

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */
Motor::Motor(void)
{
	Servo sir;
	// sir.writeMicroseconds(1500);
	// delay(7000);
}
/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
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
/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */
void Motor::updateMotor(float throttle)
{
	uint16_t finalmicro = 0;
	
    if( throttle < -100 ) 
    {
 			throttle = -100;
			finalmicro = REV_SIG;
 	}	
    else if( throttle > 100) 
    {
 			throttle = 100;
			finalmicro = FWD_SIG;
 	}
	else if( throttle > 0) 
    {
			
			finalmicro = ((FWD_SIG - STOP_SIG)*(throttle/100) + STOP_SIG);
			//finalmicro = 1600;
 	}
	else if( throttle < 0) 
    {
			
			finalmicro = (( STOP_SIG - REV_SIG)*(throttle/100) + REV_SIG);
			
 	}
	 else if( throttle = 0) 
    {
			
			finalmicro = STOP_SIG;
 	}	
    else  
    {
 			printf("Houston	we have a problem");
 	}

 	//printf("The duty cycle is: %d\n", throttle_Sig);

	sir.writeMicroseconds(finalmicro);
	Serial.print(finalmicro);
	//esc->THROTTLE_SIG = throttle_Sig; //example line of code to set throttle
	// -100 corresponds to 1100 and 100 corresponds to 1900
	// I need to scale the values from -100 and 100 to the range of 1100 to 1900
	//float onTime = (esc->STOP_SIG + throttle_Sig*4)*(1.0/1000); // This line gives us the "on-time" of the ESC in seconds
	//float dtyCycle = (onTime/esc->PER)*(1.0/10); // Calculates the duty cycle
	// line of math = threshold (thrsh); auto-reload - (duty cycle * auto-reload)
	//float thrsh = esc->AUTO_RLD - dtyCycle*esc->AUTO_RLD;
	//*(esc->ESC_TMRCH_CCR) = thrsh;
	return;
}