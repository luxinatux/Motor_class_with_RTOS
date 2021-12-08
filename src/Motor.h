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
#include <Servo.h>

#ifndef _MOTOR_H_
#define _MOTOR_H_

class Motor
{
    protected:
        uint16_t OP_FREQ; // The operating frequency of the ESC
		uint16_t FWD_SIG; // The value of the max forward throttle signal, 1.9 ms
		uint16_t REV_SIG; // The value of the max reverse throttle signal, 1.1 ms
		uint16_t STOP_SIG; // The value of the stop signal, 1.5 ms
        byte SERVO_PIN; // Pin that we will be sending PWm Through
		Servo sir;

    public:

		Motor(void);
        void initialize(byte in_pin, uint16_t fwd_sig, uint16_t Reverse, uint16_t stop); //initializing the motor
        void updateMotor(float throttle);
};