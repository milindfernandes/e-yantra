/*
* File name: Experiment-2
* Description: This experiment is a part of Task 5. It is aimed to get you familiar with the pulse width modulation.
* This experiment involves writing a code to decelerate(reduce the speed) of the robot and indicate this on the Bar Graph LEDs.
  Author: e-Yantra Team
*/
#define __DELAY_BACKWARD_COMPATIBLE__  //CodeBlocks 16.01
#define __OPTIMIZE__ -O0
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
*	Global Variable Declaration
*/
// Declare any global variable if you require here


/*
* Function Name: motion_pin_config
* Input: none
* Output: none
* Logic: Code to initialize desired I/O port using I/O port registers
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
Function name: port_init
Input: none
Output: none
Logic: Code to initialize desired I/O port using I/O port registers viz. DDRx and PORTx
Example Call: port_init();
*/

void port_init(void)
{
	DDRJ =	0xFF;				// DDRJ register is used to initialize PortJ as output port.
	//All 8 pins of PortJ is connected to 8 LEDs of Bar graph LED module.
	//Write suitable value to ensure all 8 LEDs of Bar LED can be used.

	PORTJ = 0xFF;			// PORTJ register is used to turn on/off an output device.
	//Write suitable value to ensure all 8 LEDs of Bar LED is turned ON at the start.

}

/*
* Function Name: motion_timer5_init
* Input: none
* Output: none
* Logic: Code to initialize the register to generate the PWM using timer 5
		 viz. TCCR5A,TCCR5B,TCNT5H,TCNT5L,OCR5AL and OCR5BL
Example Call: motion_timer5_init ()
*/
// Timer 5 initialized in PWM mode for velocity control
// Prescale:256
// PWM 8bit fast, TOP=0x00FF
// Timer Frequency:225.000Hz
void motion_timer5_init()
{
	TCCR5B = 0x80;	//Stop the timer initially
	TCNT5H = 0xFF;	//Counter higher 8-bit value to which OCR5xL value is compared with
	TCNT5L = 0x00;	//Counter lower 8-bit value to which OCR5xL value is compared with
	OCR5AL = 0xFF;	//Output compare register low value for Left Motor
	OCR5BL = 0xFF;	//Output compare register low value for Right Motor
	TCCR5A = 0xA9;	//Write suitable value in this register to override normal port functionality and to select Fast PWM 8-bit Mode.

	TCCR5B = 0x0B;	//Write suitable value in this register to set the desired waveform generation mode and to select a prescalar of 64.

}


// Function for robot velocity control
/*
* Function Name: velocity
* Input: none
* Output: none
* Logic: Function for robot velocity control
Example Call: velocity (left motor velocity, right motor velocity)
*/
void velocity (unsigned char left_motor, unsigned char right_motor)
{
	OCR5AL = (unsigned char)left_motor;
	OCR5BL = (unsigned char)right_motor;
}

//Function used for setting motor's direction
/*
* Function Name: forward
* Input: none
* Output: none
* Logic: Code used for setting motor's direction
		 viz.PORTx.
Example Call: forward()
*/
void forward (void)
{
  PORTA= 0x06; //define the port to rotate both wheels forward
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
  PORTA= 0x00; //define the port to stop the motor
}
/*
* Function Name: motion_barLED
* Input: none
* Output: none
Example Call: motion_barLED()
*/
void motion_barLED()
{

	// Define a forward function to move the robot in forward direction.

	/***********************************************************************
				WRITE YOUR CODE HERE. Please write inline comments.

	************************************************************************/
    _delay_ms(1000); //wait for 1 second before starting
    int i = 0;
    for (i=0;i<8;i++)
    {
        velocity(255-i*20,255-i*20); // reduce velocity every 4 seconds by 1/8th value
        forward();  // move forward for 4 seconds
        _delay_ms(4000);
        PORTJ = PORTJ >> 1 | 0x00; // decrement the bar graph by one from top
    }
    stop(); // Stop


}



//Main Function
int main()
{

	motion_pin_config();
	motion_timer5_init();
	port_init();
		// sample function call
	motion_barLED();
    return 1;
}

