#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task_imu_data_x.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <shares.h>





void task_imu_data_x(void* imu_data_x)
{
    MPU6050 mpu;

    mpu.initialize();

    int16_t gx, gy, gz;


    uint8_t fifoBuffer[64];
    Quaternion q;
    float euler[3];
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
