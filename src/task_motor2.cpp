/** @file task_motor2.cpp
 *    This file contains code for the task_motor2 function.
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>
#include <task_motor2.h>
#include <Servo.h>
#include <Motor.h>

/** @brief   Implement Motor class using values from task_controller
 *  @details This task gets updated data from the controller task (task_controller)
 *           and utilizes the Motor class to send the correct PWM signal for the
 *           desired rotation for Motor 2.
 */


void task_motor2 (void* data)
{
    (void)data;

    // Create motor1 object
    Motor motor2;

    // Initiallize the ESC connected to pin D5
    motor2.initialize(D5, 1900, 1100, 1500);
    float throttle = 0.0;
    for (;;)
    {
        // Revieve throttle amount from controller
        throttle = controller_update_y.get();

        motor2.updateMotor(throttle);

        // Motor will change direction at equal speed every x ms
        //vTaskDelay(x);


    }
}