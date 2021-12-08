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
#include <PrintStream.h>
#include <STM32FreeRTOS.h>
#include <shares.h>
#include <taskqueue.h>
#include <taskshare.h>


#include "task_imu_data.h"
#include "task_motor1.h"
#include "task_controller_x.h"



//Share<float> fft_share_gx ("FFT gx Data");
//Share<float> fft_share_gy ("FFT gy Data");

Queue<float> imu_queue_gx (256, "gx Data");
Queue<float> imu_queue_gy (256, "gy Data");

//Queue<float> omega_queue_x (256, "Omega x");
//Queue<float> omega_queue_y (256, "Omega x");

Share<float> imu_share_raw_x ("Raw x data"); 
Share<float> imu_share_raw_y ("Raw y data");

Share<float> controller_update_x ("Throttle Signal x"); 
Share<float> controller_update_y ("Throttle Signal y");

//Share<uint8_t> controller_state("choosing which controller state");



/** @brief   Arduino setup function which runs once at program startup.
 *  @details This function sets up a serial port for communication and creates
 *           the tasks which will be run.
 */
void setup () 
{
    // Start the serial port, wait a short time, then say hello. Use the
    // non-RTOS delay() function because the RTOS hasn't been started yet
    Serial.begin (115200);
    delay (2000);
    Serial << endl << endl << "Hello, I am an RTOS demonstration" << endl;

    // My TASKS FOR RTOS
    xTaskCreate(task_imu_data,
                 "Data Acq.",
                 4096,
                 NULL,
                 1,
                 NULL);

    xTaskCreate(task_motor1,
                 "Motor Control x",
                 4096,
                 NULL,
                 1,
                 NULL);
    xTaskCreate(task_motor2,
                 "Motor Control y",
                 4096,
                 NULL,
                 1,
                 NULL);
  
    xTaskCreate(task_controller_x,
              "Controller",
              2048,
              NULL,
              2,
              NULL);

    // xTaskCreate(task_fft,
    //           "FFT",
    //           4096,
    //           NULL,
    //           6,
    //           NULL);

    // If using an STM32, we need to call the scheduler startup function now;
    // if using an ESP32, it has already been called for us
    #if (defined STM32L4xx || defined STM32F4xx)
        vTaskStartScheduler ();
    #endif
}


/** @brief   Arduino's low-priority loop function, which we don't use.
 *  @details A non-RTOS Arduino program runs all of its continuously running
 *           code in this function after @c setup() has finished. When using
 *           FreeRTOS, @c loop() implements a low priority task on most
 *           microcontrollers and crashes on some others, so we'll not use it.
 */
void loop () 
{
}
