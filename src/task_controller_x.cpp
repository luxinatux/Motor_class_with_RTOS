/*  This task needs to take all of the data and decide what to do with it.
    All direct 

*/
#include <Arduino.h>
#include <task_imu_data_x.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <STM32FreeRTOS.h>
#include <shares.h>
#include <task_controller_x.h>
#include <Motor.h>

Motor motor1;
Motor motor2;

const int16_t queue_size = 256;
int16_t theta_x[queue_size], theta_y[queue_size];
int16_t omega_x[queue_size], omega_y[queue_size];

int16_t raw_x1;
int16_t raw_x2;
int16_t omega_raw_x[4];

void task_controller_x(void* gxdata)
{
    for(;;)
    {
        // Get imu queue data
        *theta_x = imu_queue_gx.get();

        raw_x1 = imu_queue_raw_x.get();
        raw_x2 = imu_queue_raw_x.get();

        int16_t raw_x = raw_x2 - raw_x1;

        imu_share_raw_x.put(raw_x);


        // Calculate angualar velocity, put values into new array
        for (uint8_t index = 1; index < queue_size; index++)
        {
            omega_x[index] = (theta_x[index] - theta_x[index-1])*(180/3.14)/100;
            omega_queue_x.put(omega_x[index]);
        }


        // Input share data into motor class to get output value
        //int16_t gx = motor1.change(gx_queue);
        //int16_t gy = motor2.change(gy_queue);

        // Get FFT data
        // int16_t gx_fft = fft_share_gx.get();
        // int16_t gy_fft = fft_share_gy.get();

    }
}