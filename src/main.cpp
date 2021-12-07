/** @file main.cpp
 *    This file contains a simple demonstration program for ME507 which uses
 *    FreeRTOS to do multitasking. One of the tasks makes a square wave which
 *    can be viewed and measured with a signal analyzer or oscilloscope, while
 *    other tasks just print fairly useless things to the serial port. 
 * 
 *  @author JR Ridgely
 *  @date   28 Sep 2020 Original file
 *  @date    9 Oct 2020 Added another task because I got bored
 *  @date   19 Oct 2021 Changed a task from simulation to real square waves
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "task_square.h"           // Header for square wave task module
#include "tasks_ui.h"              // Header for user interface task module


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

    // Create a task which prints a slightly disagreeable message

    //Ridgely Stuff

    xTaskCreate (task_ui,
                 "UI",                            // Task name for printouts
                 4096,                            // Stack size
                 NULL,                            // Parameters for task fn.
                 1,                               // Priority
                 NULL);                           // Task handle

    // My TASKS FOR RTOS
    xTaskCreate(task_imu_data,
                 "Data Acq.",
                 4096,
                 NULL,
                 1,
                 NULL);
  
    // xTaskCreate(task_controller_x,
    //           "Control",
    //           2048,
    //           NULL,
    //           2,
    //           NULL);

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
