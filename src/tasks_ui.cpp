/** @file tasks_ui.cpp
 *  This file contains tasks which interact with a user. As these tasks support
 *  a very simple demonstration of multitasking, they don't do very much.
 * 
 *  @author  JR Ridgely
 *  @date    2021-Oct-19 Original file
 */

#include "tasks_ui.h"


/** @brief   Task which interacts with a user. 
 *  @details This task occasionally sends some information to a user.
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_ui (void* p_params)
{
    (void)p_params;            // Does nothing but shut up a compiler warning

    for (;;)
    {
        Serial << "u";

        // Delay the given number of RTOS ticks until beginning to run this
        // task loop again. The resulting timing is not accurate, as the time
        // it took to run the task adds to this interval and accumulates
        vTaskDelay (2500);
    }
}


/** @brief   Task which occasionally prints a carriage return.
 *  @details Since the serial monitor gets all ugly when we don't end lines at
 *           reasonable intervals, this task prints a carriage return now and
 *           then.
 *  @param   p_params A pointer to function parameters which we don't use.
 */
void task_returns (void* p_params)
{
    (void)p_params;            // Does nothing but shut up a compiler warning

    for (;;)
    {
        Serial << endl;

        // Delay the given number of RTOS ticks to run about twice a minute
        vTaskDelay (30000);
    }
}

