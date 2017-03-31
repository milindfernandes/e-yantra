
/*
*
* File name: Experiment-2
* Description: This experiment is a part of Task 6. It is aimed to get you familiar with whiteline following.
* This experiment involves writing a code to make the robot follow a white line.
  Author: e-Yantra Team
*/

#define __OPTIMIZE__ -O0
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "lcd.h"

/*
*	Global Variable Declaration
*/
// Declare any global variable if you require here

#define THRESHOLD 50


///////////////////////////////////LCD initialization ///////////////////////////////
/*
* Function Name: lcd_port_config
* Input: none
* Output: none
* Logic: Code to initialize desired I/O port using IO port registers
		 viz. DDRx and PORTx.
Example Call: lcd_port_config
*/

void lcd_port_config ()
	{

	 DDRC= DDRC | 0xF7; // All Port C pins except Pin no. 4 i.e(PC3) have to be set as output.

	 PORTC= PORTC & 0x08 ; // Write suitable value in the PORT C register to make initial values to be "0"
	 		  //Set initial value as "0" on all pins except Pin no.4 (PC3)

	}
//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////ADC related functions////////////////////////////////////
/*
* Function Name: adc_pin_config
* Input: none
* Output: none
* Logic: Code to initialize desired I/O port using IO port registers
		 viz. DDRx and PORTx.
Example Call: adc_pin_config
*/
void adc_pin_config (void)
{
 DDRF = 0x00 ;// All Port F pins have to be set as input.
 PORTF = 0x00 ;// Write suitable value in the PORT F register to make initial values to be "0"
 DDRK = 0x00 ;//All Port K pins have to be set as input
 PORTK = 0x00 ;// Write suitable value in the PORT K register to make initial values to be "0"
}



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
 DDRA = DDRA | 0x0F ;	//  Port A pins(PA3-PA0) have to be set as outputs.
 PORTA = PORTA & 0xF0;	// Write suitable value in the PORT A register to make initial values to be "0"
 DDRL = DDRL | 0x18 ;  	//Setting PL3 and PL4 pins as output for PWM generation
 PORTL = PORTL | 0x18 ;	////Write suitable value in the PORT L register to set initial value of the Port L pins (PL3, PL4) to logic 1.
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
	TCCR5B = 0x00 ;	//Stop the timer initially
	TCNT5H = 0xFF ;	//Counter higher 8-bit value to which OCR5xL value is compared with
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
/*
* Function Name: adc_init
* Input: none
* Output: none
* Logic: Code to initialize the register to generate the PWM using timer 5
		 viz. ADCSRA,ADCSRB,ADMUX,ACSR
Example Call: adc_init()
*/
void adc_init()
{
	ADCSRA = 0x00;	//Write suitable value in this register to disable ADC during initialization.
	ADCSRB = 0x00;	//Write suitable value in this register for initialization.
	ADMUX = 0x20;	//Write appropraite value in the ADMUX register to select external Reference voltage (connected to AREF pin) and left adjustment active.
	ACSR =  0x80;	//Disable the analog comparator.
	ADCSRA = 0x86;	//Write suitable value to this register to enable ADC and to select the required prescalar.
}

/*
* Function Name: ADC_Conversion_wl_sensor
* Input: ADC Channel number
* Output: Digital value
* Logic: Code to convert the analog value of the three whiteline sensors into digital value.
Example Call: ADC_Conversion_wl_sensor( ADC channel number)
*/

//Function For ADC Conversion
unsigned char ADC_Conversion_wl_sensor(unsigned char Ch)
{
	//This function accepts ADC channel number as an input and returns the digital equivalent of the analog value read by the sensor.
	// Complete the code to write appropriate value in the ADMUX register based on the input channel number passed.
	// Start the ADC conversion and return its digital equivalent value.
    unsigned char adc_val;
    if(Ch > 7){
        ADCSRB = ADCSRB | 0x08;
    }
    Ch = Ch & 0x07;
    ADMUX = 0x20 | Ch;
    ADCSRA = ADCSRA | 0x40;
    while((ADCSRA & 0x10)==0);
    adc_val = ADCH;
    ADCSRA = ADCSRA | 0x10;
    ADCSRB = 0x00;
    return adc_val;
}

/*
* Function Name: ADC_Conversion_sharp_sensor
* Input: none
* Output: none
* Logic: Code to convert the analog value of the front sharp IR range sensor into digital value.
Example Call: ADC_Conversion_sharp_sensor
*/

//unsigned char ADC_Conversion_sharp_sensor()
//{

	// Complete the code to write appropriate value in the ADMUX register based on the ADC channel number of the front sharp IR range sensor.
	// Start the ADC conversion and return its digital equivalent value.
	//front sharp sensor is connected to ADC channel number 11.
//}
void forward (void)
{
    PORTA= PORTA | 0x06; //define the port to rotate both wheels forward
}

void stop (void)
{
  PORTA= PORTA & 0xF0; //define the port to stop the motor
}




int main()
{
lcd_port_config();
motion_pin_config();
adc_pin_config();
adc_init();
lcd_init();
motion_timer5_init();
unsigned char wLineLeft, wLineRight, wLineCenter;
while(1)
{

  //Read the three white line sensor values.
  //Read the front sharp sensor value.

  //write code to implement white line following algorithm. Refer to the tutorial uploaded on the portal.

  //stop the robot if any obstacle is detected within 15 cm distance
  //You can use lcd_print function to print the sensor values for better debugging.
    int distance;
    distance = (int)(10.00*(2799.6*(1.00/(pow(ADC_Conversion_wl_sensor(11),1.1546)))));
    lcd_print(1,13,(int)distance,3);
   while(distance > 100){
        wLineRight = ADC_Conversion_wl_sensor(1);
        wLineCenter = ADC_Conversion_wl_sensor(2);
        wLineLeft = ADC_Conversion_wl_sensor(3);
        lcd_print(1,1,(int)wLineLeft,3);
        lcd_print(1,5,(int)wLineCenter,3);
        lcd_print(1,9,(int)wLineRight,3);

        if(wLineLeft < THRESHOLD){
            //turn left
            forward();
            velocity(100,150);
            lcd_cursor(2,1);
            lcd_string("left");
        }
        if(wLineRight < THRESHOLD){
            //turn right
            forward();
            velocity(150,100);
            lcd_cursor(2,1);
            lcd_string("right");
        }
        if(wLineCenter < THRESHOLD && (wLineRight > THRESHOLD) && (wLineLeft > THRESHOLD)){
            forward();
            velocity(150,150);
            lcd_cursor(2,1);
            lcd_string("forward");
        }
        distance = (int)(10.00*(2799.6*(1.00/(pow(ADC_Conversion_wl_sensor(11),1.1546)))));
   }
   stop();



}

}





