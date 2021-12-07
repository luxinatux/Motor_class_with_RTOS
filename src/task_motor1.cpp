#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <shares.h>
#include <task_motor1.h>
#include <Servo.h>
#include <Motor.h>



// Need to figure out how fast the motor should turn in each direction
void task_motor1 (void* data)
{
    (void)data;
    Motor motor1;
    motor1.initialize(D6, 1900, 1100, 1500);
    float throttle = 0.0;
    for (;;)
    {
        // Get fundamental frequency
        throttle = controller_update_x.get();

        motor1.updateMotor(throttle);

        // Motor will change direction at equal speed every x ms
        //vTaskDelay(x);


    }
}