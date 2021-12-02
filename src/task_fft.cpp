#include <Arduino.h>
#include <task_imu_data_x.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <STM32FreeRTOS.h>
#include <task_fft.h>
#include <fft.h>
#include <shares.h>

const uint16_t queue_size = 256;
int16_t gx[queue_size], gy[queue_size];

void task_fft(void* newgxdata)
{

    for(;;) 
    {
        // Getting x and y gyro data in the queue
        *gx = omega_queue_x.get();

        // Creating a new empty complex array for FFT
        complex *gxfft = new complex[queue_size];

        // Fill the complex arrays with imu data
        for (uint8_t index = 0; index < queue_size; index++)
        {
            gxfft[index] = gx[index];
        }

        //Performing forward FFT on x and y gyro data
        CFFT::Forward(gxfft, queue_size);

        // Getting real values
        int16_t gxnewre = gxfft->re();

        fft_share_gx.put(gxnewre);
    }
        
}