/** @file task_square.cpp
 *  This file contains a task for a simple RTOS demonstration program. This
 *  task runs periodically and creates a square wave which can be viewed using
 *  an oscilloscope or logic analyzer.
 * 
 *  @author  JR Ridgely
 *  @date    2021-Oct-19 Original file
 */

#include <Arduino.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "task_square.h"

/// The number of RTOS ticks between runs of the square wave task
const TickType_t SQUARE_HALF_PERIOD = 25;

/// The pin used for sending square waves on either a Nucleo or ESP32 board
#ifdef ESP32
    const uint8_t SQUARE_PIN = 23;
#else                                   // If not ESP32, we assume STM32 Nucleo
    const uint8_t SQUARE_PIN = PC0;
#endif


/** @brief   Task which produces a square wave.
 *  @details This task runs at precise interfals using @c vTaskDelayUntil() and
 *           produces a square wave which can be read with an oscilloscope or
 *           logic analyzer.
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_square (void* p_params)
{
    (void)p_params;                             // Shuts up a compiler warning

    // Initialise the xLastWakeTime variable with the current time.
    // It will be used to run the task at precise intervals
    TickType_t xLastWakeTime = xTaskGetTickCount();

    // In order to see anything, one must set the square wave pin as an output
    pinMode (SQUARE_PIN, OUTPUT);

    for (;;)
    {
        // Toggle the square wave pin. The value written is LOW if reading the
        // pin returns HIGH (which is true) and HIGH if the pin has been LOW
        digitalWrite (SQUARE_PIN, (digitalRead (SQUARE_PIN) ? LOW : HIGH));

        // This type of delay waits until it has been the given number of RTOS
        // ticks since the task previously began running. This prevents timing
        // inaccuracy due to not accounting for how long the task took to run
        vTaskDelayUntil (&xLastWakeTime, SQUARE_HALF_PERIOD);
    }
}


