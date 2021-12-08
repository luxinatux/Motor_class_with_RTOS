// /*  This task needs to take all of the data and decide what to do with it.
//     All direct 


#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task_imu_data.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#include <shares.h>
#include <task_controller_x.h>
#include <Motor.h>



void task_controller_x(void* gxdata)
{
    (void)gxdata;
    const int16_t queue_size = 256;
    int16_t theta_x1, theta_x2, theta_y1, theta_y2;
    int16_t omega_x, omega_y;
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
    float J_mug = (mug_mass/12)*(3*(i_r*i_r + o_r*o_r) + (height*height));

    // Reaction wheel dynamics
    float motor_mass = 0.049; //motor mass in [kg]
    float wheel_mass = ;
    float fly_radius = ;
    float fly_mass = motor_mass + wheel_mass;
    float I_flywheel = 0.5*fly_mass*fly_radius;

    // Controller Variables
    float range = 90;
    float P = 0.0;
    float D = 0.25;

    //Timing 
    TickType_t first_tick;
    TickType_t prev_tick = xTaskGetTickCount();

    for(;;)
    {
        // Get imu queue data
        first_tick = xTaskGetTickCount();
        theta_x1 = imu_share_raw_x.get();
        theta_x2 = imu_share_raw_x.get();

        // Calculate angular acceleration, put values into new array
        alpha_x = (theta_x1 - theta_x2)*(3.14/180)/(first_tick - prev_tick);

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