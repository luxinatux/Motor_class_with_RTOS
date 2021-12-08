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
#include <task_imu_data.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#include <shares.h>
#include <task_controller_x.h>
#include <Motor.h>

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

void task_controller_x(void* gxdata)
{
    (void)gxdata;
    const int16_t queue_size = 256;
    int16_t theta_x1, theta_x2, theta_y1, theta_y2;
    int16_t omega_x1, omega_x2;
    int16_t omega_y1, omega_y2;
    int16_t alpha_x, alpha_y;

    int16_t raw_x1;
    int16_t raw_x2;
    int16_t omega_raw_x[4];
    uint16_t counter = 1;

    // Mug Dynamics for Polar Moment of Intertia
    float i_r = 0.098425; // Mug inner radius[m]
    float o_r = 0.104775; // Mug outer radius [m]
    float height = 0.1651; // Mug height overall [m]
    float mug_mass = 0.82; // Mug weight [kg]
    float I_mug = (mug_mass/12)*(3*(i_r*i_r + o_r*o_r) + (height*height));
    

    // Reaction wheel dynamics
    float motor_mass = 0.049; //motor mass in [kg]
    float wheel_mass = 0.058; //weight of ideal machined wheel [kg]
    float fly_radius = 0.01524; // 0.6 in for ideal machined wheels [m]
    float fly_mass = motor_mass + wheel_mass;
    float I_flywheel = 0.5*fly_mass*fly_radius*fly_radius;

    // Controller Variables
    float range = 90;
    float P = 0.0;
    float D = 0.25;

    // Throttle Control
    float torque_needed;
    float previous_throttle;
    float current_throttle;


    //Timing 
    TickType_t first_tick;
    TickType_t prev_tick = xTaskGetTickCount();

    for(;;)
    {
        
        first_tick = xTaskGetTickCount();
        
        // Get imu queue data
        omega_x1 = imu_share_raw_x.get();
        omega_x2 = imu_share_raw_x.get();

        // Calculate angular acceleration, put values into new array
        alpha_x = (omega_x1 - omega_x2)*(3.14/180)*(1000)/(first_tick - prev_tick);

        torque_needed = 

        // Initialise the xLastWakeTime variable with the current time.
        // It will be used to run the task at precise intervals
        
      


        // Input share data into motor class to get output value
        //int16_t gx = motor1.change(gx_queue);
        //int16_t gy = motor2.change(gy_queue);

        // Get FFT data
        // int16_t gx_fft = fft_share_gx.get();
        // int16_t gy_fft = fft_share_gy.get();

    }
}