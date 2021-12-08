/** @file main.cpp
 *    This file contains code for the task_imu_data function
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

/** @brief   Collect IMU angular velocity data.
 *  @details Iniitialize the IMU and collect the angular acceleration data
 *           in the x and y directions and put the data into shares and queues.
 */

void task_imu_data(void* imu_data)
{
    (void)imu_data;
    
    // Begin I2C connection
    Wire.begin();

    // Create mpu object
    MPU6050 mpu;

    // Initialize the IMU
    mpu.initialize();

    float gx, gy;


    // uint8_t fifoBuffer[64];
    // Quaternion q;
    // float euler[3];

    for (;;)
    {
        // Obtain x and y raw angular acceleration output
        gx = mpu.getRotationX(); 
        gy = mpu.getRotationY();

        // Put data into shares
        imu_share_raw_x.put(gx);
        imu_share_raw_y.put(gy);

        // Put data into queues
        imu_queue_x.put(gx);
        imu_queue_y.put(gy);
        
        //Get euler angles for x and y rotation
        // mpu.dmpGetQuaternion(&q, fifoBuffer);
        // mpu.dmpGetEuler(euler, &q);

        // Put gyro data for x and y into queues
        //imu_queue_gx.put(euler[0]);
        //imu_queue_gy.put(euler[1]);

        //float angle1 = euler[0]*180/M_PI;
        //float angle2 = euler[1]*180/M_PI;

        // Delay every 10 ms so angular acceleration can be calculation from angular position
        vTaskDelay(10);
    }
}
