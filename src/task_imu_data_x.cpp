#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task_imu_data_x.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <shares.h>
#include <MPU6050_6Axis_MotionApps20.h>

MPU6050_6Axis_MotionApps20 mpu;

int16_t gx, gy, gz;

uint8_t fifoBuffer[64];
Quaternion q;
float euler[3];



void task_imu_data_x(void* imu_data_x)
{
    for (;;)
    {
        // Obtain x and y gyro data
        imu_queue_raw_x.put(mpu.getRotationX());
        //mpu.getRotationY();
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);

        // Put gyro data for x and y into shared variable
        imu_share_gx.put(euler[0]);
        
        

        // Put gyro data for x and y into queues
        imu_queue_gx.put(euler[0]);


        vTaskDelay(10);
    }
}
