/** @file main.cpp
 *    This file contains code for the task_fft_y function.
 * 
 *  @author Lucas Martos-Repath & Garret Gilmore
 *  @date   15 Nov 2021 Original file
 *  @date   7 Dec 2021
 */


#include <Arduino.h>
#include <task_imu_data.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <STM32FreeRTOS.h>
#include <task_fft_y.h>
#include <fft.h>
#include <shares.h>



/** @brief   Perform FFT algorithm on raw IMU angular velocity data.
 *  @details Gets IMU queue data for the y rotation from task_imu_data and puts it into a newly
 *           created complex array. This array is then ran through an FFT algorithm
 *           and the new data is put into a share which is sent to the controller task.
 */

void task_fft_y(void* newgydata)
{
    uint16_t counter = 0;
    const uint16_t queue_size = 256;
    float gy;
    for(;;) 
    {
        // Getting x and y gyro data in the queue
        gy = imu_queue_y.get();

        // Creating a new empty complex array for FFT
        complex *gyfft = new complex[queue_size];

        // Fill the complex arrays with imu data
        if (counter++ < queue_size)
        {
            gyfft[counter] = gy;
        }

        //Performing forward FFT on x and y gyro data
        CFFT::Forward(gyfft, queue_size);

        // Getting real values
        int16_t gynewre = gyfft->re();

        fft_share_gy.put(gynewre);
    }
        
}