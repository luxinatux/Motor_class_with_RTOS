/** @file task_controller_x.cpp
 *    This file contains our design of a controller and its implementation into
 *    task form. Initially we believed a need for two controller tasks to
 *    handle each individual motor, but have isolated it down into one task.  
 *    This task tries to shown implementation of a time oriented update for the 
 *    motor throttle. This update to the motor throttle is stored in a share and 
 *    to each of the motor tasks directly.
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   28 Nov 2021 Original file
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

/** @brief   Recieve Data from the IMU and convert it into a Throttle signal
 *  @details This task is especially detailed with mug dynamics and messiness 
 *           all over. This task has iteration upon iteration, semi left to show 
 *           work we put in to try to get it running. This task takes available 
 *           angular velocity data when applicable, and calculates an acceleration 
 *           based on the clock ticks from one calculation to the next. It then uses 
 *           a PD controller to output a throttle signal.
 *  @param   number The number which is to be printed
 */

void task_controller_x(void* gxdata)
{
    (void)gxdata; // for compiler
    const int16_t queue_size = 256; // queue sizes
    int16_t theta_x1, theta_x2, theta_y1, theta_y2; // angles output by IMU, removed due to Euler angles not reading in tasks
    int16_t omega_x1, omega_x2; //raw angular velocity data from IMU
    int16_t omega_y1, omega_y2; //raw angular velocity data from IMU
    int16_t alpha_x, alpha_y; //calculated angular acceleration from angular Velocity

    

    // OLD Variables
    // int16_t raw_x1;
    // int16_t raw_x2;
    // int16_t omega_raw_x[4];
    // uint16_t counter = 1;

    // Mug Dynamics for Polar Moment of Intertia
    float i_r = 0.098425; // Mug inner radius[m]
    float o_r = 0.104775; // Mug outer radius [m]
    float height = 0.1651; // Mug height overall [m]
    float mug_mass = 0.82; // Mug weight [kg]
    float I_mug = (mug_mass/12)*(3*(i_r*i_r + o_r*o_r) + (height*height)); // Estimated Mug moment of intertia
    

    // Reaction wheel dynamics
    float motor_mass = 0.049; //motor mass in [kg]
    float wheel_mass = 0.058; //weight of ideal machined wheel [kg]
    float fly_radius = 0.01524; // 0.6 in for ideal machined wheels [m]
    float fly_mass = motor_mass + wheel_mass; // Total mass of System
    float I_flywheel = 0.5*fly_mass*fly_radius*fly_radius; // Estimate moment of Intertia for rotating flywheel

    // Controller Variables
    
    float P = 0.0; 
    float D = 0.25;

    // Throttle Control
    float torque_needed;
    float previous_throttle_x = 50;
    float current_throttle_x;
    float previous_throttle_y = 50;
    float current_throttle_y;
    float max_change = 20.0;
    float Forward_saturation = 95;
    float reverse_saturation = 5;
    float range = Forward_saturation - reverse_saturation; // throttle range
    float return_to_steady = 2;

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

        current_throttle_x = previous_throttle_x + ((P * omega_x2) + (D * alpha_x));
        if((current_throttle - previous_throttle) > max_change)
        {
            current_throttle_x = previous_throttle_x + max_change;
        }


        controller_update_x.put(current_throttle_x)
        // Initialise the xLastWakeTime variable with the current time.
        // It will be used to run the task at precise intervals
        
        prev_tick = first_tick;


        // Input share data into motor class to get output value
        //int16_t gx = motor1.change(gx_queue);
        //int16_t gy = motor2.change(gy_queue);

        // Get FFT data
        // int16_t gx_fft = fft_share_gx.get();
        // int16_t gy_fft = fft_share_gy.get();

    }
}