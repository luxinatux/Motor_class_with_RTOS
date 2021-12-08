/** @file main.cpp
 *    This file contains code for the task_fft function.
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
#include <task_fft.h>
#include <fft.h>
#include <shares.h>



/** @brief   Perform FFT algorithm on raw IMU angular velocity data.
 *  @details Gets IMU queue data from task_imu_data and puts it into a newly
 *           created complex array. This array is then ran through an FFT algorithm
 *           and the new data is put into a share which is sent to the controller task.
 *  @param   number The number which is to be printed
 */

void task_fft(void* newgxdata)
{
    uint16_t counter = 0;
    const uint16_t queue_size = 256;
    float gx;
    for(;;) 
    {
        // Getting x and y gyro data in the queue
        gx = imu_queue_x.get();

        // Creating a new empty complex array for FFT
        complex *gxfft = new complex[queue_size];

        // Fill the complex arrays with imu data
        if (counter++ < queue_size)
        {
            gxfft[counter] = gx;
        }

        //Performing forward FFT on x and y gyro data
        CFFT::Forward(gxfft, queue_size);

        // Getting real values
        int16_t gxnewre = gxfft->re();

        fft_share_gx.put(gxnewre);
    }
        
}