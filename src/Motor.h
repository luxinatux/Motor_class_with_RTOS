#include <Arduino.h>
#include <Servo.h>


class Motor
{
    protected:
        uint16_t OP_FREQ; // The operating frequency of the ESC
		uint16_t FWD_SIG; // The value of the max forward throttle signal, 1.9 ms
		uint16_t REV_SIG; // The value of the max reverse throttle signal, 1.1 ms
		uint16_t STOP_SIG; // The value of the stop signal, 1.5 ms
        byte SERVO_PIN; // Pin that we will be sending PWm Through
		Servo sir;
		//uint32_t* ESC_TMRCH_CCR; // The compare/capture register at which the timer will be set
		//uint32_t AUTO_RLD; // The value at which the timer will overflow
		//float PER; // Period of the timer
		//float THROTTLE_SIG; // The throttle signal passed by the MCU to the ESC

    public:

		Motor(void);
        void initialize(byte in_pin, uint16_t fwd_sig, uint16_t Reverse, uint16_t stop); //initializing the motor
        void updateMotor(float throttle);




};