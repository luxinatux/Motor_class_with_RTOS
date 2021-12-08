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
#include <STM32FreeRTOS.h>
#include <task_imu_data.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <shares.h>
#include <Wire.h>

/** @brief   Print a number, saying that it's a number.
 *  @details This is not a particularly useful function, except that it
 *           helps to show how a function can print things under Arduino.
 *  @param   number The number which is to be printed
 */

void task_imu_data(void* imu_data)
{
    (void)imu_data;

    Wire.begin();

    MPU6050 mpu;

    mpu.initialize();

    int16_t gx, gy, gz;


    uint8_t fifoBuffer[64];
    Quaternion q;
    float euler[3];

    for (;;)
    {
        // Obtain x and y raw angular acceleration output
        // Note: Maybe these can be shares since mpu.getRotation() calculation ang accel.
        imu_share_raw_x.put((float)mpu.getRotationX()); 
        imu_share_raw_y.put((float)mpu.getRotationY());
        
        //Get euler angles for x and y rotation
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);

        // Put gyro data for x and y into queues
        //imu_queue_gx.put(euler[0]);
        //imu_queue_gy.put(euler[1]);

        //float angle1 = euler[0]*180/M_PI;
        //float angle2 = euler[1]*180/M_PI;

        // Delay every 10 ms so angular acceleration can be calculation from angular position

        Serial.print(mpu.getRotationX());
        Serial.print("   ");
        Serial.println(mpu.getRotationY());

        vTaskDelay(100);
    }
}
