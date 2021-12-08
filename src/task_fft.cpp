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


// #include <Arduino.h>
// #include <task_imu_data.h>
// #include <I2Cdev.h>
// #include <MPU6050.h>
// #include <STM32FreeRTOS.h>
// #include <task_fft.h>
// #include <fft.h>
// #include <shares.h>



/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

// void task_fft(void* newgxdata)
// {
//     uint16_t counter = 0;
//     const uint16_t queue_size = 256;
//     int16_t gx[queue_size], gy[queue_size];
//     for(;;) 
//     {
//         // Getting x and y gyro data in the queue
//         gx = omega_queue_x.get();

//         // Creating a new empty complex array for FFT
//         complex *gxfft = new complex[queue_size];

//         // Fill the complex arrays with imu data
//         if (counter++ < queue_size)
//         {
//             gxfft[counter] = gx[counter];
//         }

//         //Performing forward FFT on x and y gyro data
//         CFFT::Forward(gxfft, queue_size);

//         // Getting real values
//         int16_t gxnewre = gxfft->re();

//         fft_share_gx.put(gxnewre);
//     }
        
// }