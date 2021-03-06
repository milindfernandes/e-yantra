/*
* File name: Experiment-1
* Description: This experiment is a part of Task 5. It is aimed to get you familiar with simple motion control of DC motor.
* This experiment involves writing a code to create a Shape "C" using motion control of DC motor.
  Author: e-Yantra Team
*/
#define __DELAY_BACKWARD_COMPATIBLE__  //CodeBlocks 16.01

#define __OPTIMIZE__ -O0
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



/*
* Function Name: motion_pin_config
* Input: none
* Output: none
* Logic: Code to initialize desired I/O port using IO port registers
		 viz. DDRx and PORTx.
Example Call: motion_pin_config ()
*/
void motion_pin_config (void)
{
 DDRA = DDRA | 0x0F;	//set direction of the PORTA pins (PA3-PA0) as output
 PORTA = PORTA & 0xF0;   // set initial value of the PORTA pins (PA3-PA0) to logic 0
 DDRL = DDRL | 0x18;  	//Setting PL3 and PL4 pins as output for PWM generation
 PORTL = PORTL | 0x18; 	//PL3 and PL4 pins are used for velocity control using PWM
}


/*
* Function Name: forward
* Input: none
* Output: none
* Logic: Code used for setting motor's direction
		 viz.PORTx.
Example Call: forward()
*/
void forward (void) //both wheels forward
{
  PORTA= PORTA & 0xF0;  // Write sutiable value in PORTA to set direction of both wheels as forward.
  PORTA = PORTA | 0x06;
}
/*
* Function Name: left
* Input: none
* Output: none
* Logic: Code used for setting motor's direction
		 viz.PORTx.
Example Call: left()
*/
void left (void)
{
 PORTA= PORTA & 0xF0;    //Write suitable value in PORTA register to rotate Left wheel backward and Right wheel forward
 PORTA = PORTA | 0x05;
}
/*
* Function Name: right
* Input: none
* Output: none
* Logic: Code used for setting motor's direction
		 viz.PORTx.
Example Call: right()
*/
void right (void)
{
  PORTA = PORTA & 0xF0; 	//Write suitable value in PORTA register to rotate Left wheel forward and Right wheel backward
  PORTA = PORTA | 0x0A;
}
/*
* Function Name: stop
* Input: none
* Output: none
* Logic: Code used for setting motor's direction
		 viz.PORTx.
Example Call: stop()
*/
void stop (void)
{
  PORTA = PORTA & 0xF0; 	//Write suitable value in PORTA register to stop the robot.

}
/*
* Function Name: create_shape
* Input: none
* Output: none
* Logic: Code to make the shape"L"
Example Call: create_shape()
*/
void create_shape()
{
	/***********************************************************************
				WRITE YOUR CODE HERE. Please write inline comments.

	************************************************************************/
	_delay_ms(1000); // wait for one second before start
	forward();
	_delay_ms(5000); // move forward for 5 seconds
	left();
	_delay_ms(560); // turn left by 90 degrees
	forward();
	_delay_ms(5000); // move forward for 10 seconds
	_delay_ms(5000);
	left();
	_delay_ms(560); // turn left by 90 degrees
	forward();
	_delay_ms(5000); // move forward for 5 seconds
	stop();
}
//Main Function
int main()
{
	motion_pin_config();

	// sample function call
	create_shape();
	return 1;
}

