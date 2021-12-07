#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <task_imu_data.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <shares.h>

void task_imu_data_x(void* imu_data)
{
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
        imu_share_raw_x.put(mpu.getRotationX()); 
        imu_share_raw_y.put(mpu.getRotationY());
        
        //Get euler angles for x and y rotation
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetEuler(euler, &q);

        // Put gyro data for x and y into queues
        imu_queue_gx.put(euler[0]);
        imu_queue_gy.put(euler[1]);

        // Delay every 10 ms so angular acceleration can be calculation from angular position

        Serial.print(euler[0]);
        Serial.print("   ");
        Serial.print(euler[1]);

        vTaskDelay(10);
    }
}
