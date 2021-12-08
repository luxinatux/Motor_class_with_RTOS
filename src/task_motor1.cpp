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
#include <STM32FreeRTOS.h>
#include <shares.h>
#include <task_motor1.h>
#include <Servo.h>
#include <Motor.h>

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

// Need to figure out how fast the motor should turn in each direction
void task_motor1 (void* data)
{
    (void)data;
    Motor motor1;
    motor1.initialize(D6, 1900, 1100, 1500);
    float throttle = 0.0;
    for (;;)
    {
        // Get fundamental frequency
        throttle = controller_update_x.get();

        motor1.updateMotor(throttle);

        // Motor will change direction at equal speed every x ms
        //vTaskDelay(x);


    }
}