/*
* File name: Experiment-1
* Description: This experiment is a part of Task 6. It is aimed to get you familiar with ADC (analog to digital conversion).
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

	 DDRC= DDRC | 0xF7  ; // All Port C pins except Pin no. 4 i.e(PC3) have to be set as output.

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
 DDRF = 0x00 ;  // All Port F pins have to be set as input.
 PORTF = 0x00; // Write suitable value in the PORT F register to make initial values to be "0"
 DDRK = 0x00; //All Port K pins have to be set as input
 PORTK = 0x00; // Write suitable value in the PORT K register to make initial values to be "0"
}


/*
* Function Name: adc_init
* Input: none
* Output: none
* Logic: Code to initialize the register to generate the PWM using timer 5
		 viz. ADCSRA,ADCSRB,ADMUX,ACSR
Example Call: adc_init())
*/
void adc_init()
{
	ADCSRA = 0x00;	//Write suitable value in this register to disable ADC during initialization.
	ADCSRB =  0x08;	//Write suitable value in this register for initialization.
	ADMUX = 0x20 ;	//Write appropriate value in the ADMUX register to select external Reference voltage (connected to AREF pin) and left adjustment active.
	ACSR = 0x80;	//Disable the analog comparator.(optional)
	ADCSRA = 0x86 ;	//Write suitable value to this register to enable ADC and to select the required prescalar.
}


/*
* Function Name: ADC_Conversion_sharp_sensor
* Input: none
* Output: none
* Logic: Code to convert the analog value of the front sharp IR range sensor into digital value.
Example Call: ADC_Conversion_sharp_sensor
*/
//Function For ADC Conversion

unsigned char ADC_Conversion_sharp_sensor()
{
	// Complete the code to write appropriate value in the ADMUX register based on the ADC channel number of the front sharp IR range sensor.
	// Start the ADC conversion and return its digital equivalent value.
	//front sharp sensor is connected to ADC channel number 11
	unsigned char adc_val;
    ADMUX = 0x23;
    ADCSRA = ADCSRA | 0x40;
    while((ADCSRA & 0x10)==0);
    adc_val = ADCH;
    ADCSRA = ADCSRA | 0x10;
    return adc_val;
}


/*

* Function Name: Sharp_GP2D12_estimation
* Input: digital value of sharp sensor reading
* Output: distance in mm
* Logic: Code to approximate the relationship between the output voltage of the sharp sensor
and the distance of the object from it.
Example Call: Sharp_GP2D12_estimation(ADC reading of sharp sensor)
*/
//Function For ADC Conversion

unsigned int Sharp_GP2D12_estimation(unsigned char adc_reading)
{
	float distance;
	unsigned int distanceInt;
	distance = (int)(10.00*(2799.6*(1.00/(pow(adc_reading,1.1546)))));
	distanceInt = (int)distance;
	if(distanceInt>800)
	{
		distanceInt=800;
	}
	return distanceInt;
}
////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////main function////////////////////////////////////////////

int main()
{
	lcd_port_config();
	lcd_init();
    lcd_cursor(1,1);
	lcd_string("Obstacle is ");
	adc_pin_config();
	adc_init();
	unsigned char adc_val;
	unsigned int dist;
	while(1)
	{

 	////write code to read sharp sensor values and display message on LCD accordingly//////

	//////example to print the position of Obstacle value on lcd/////////////////////

		/*	lcd_cursor(1,1);
			lcd_string("Obstacle is far");
		*/

//////////////////////////////////////////////////////////////////////////
        adc_val = ADC_Conversion_sharp_sensor();
        dist = Sharp_GP2D12_estimation(adc_val);
        //lcd_print (2, 5, dist, 3);
        //lcd_cursor(2,5);
        //lcd_wr_char(adc_val);
        if (dist > 100 && dist < 200){
            lcd_cursor(2,1);
			lcd_string("   ");
            lcd_cursor(1,13);
			lcd_string("near");
        }
        if(dist > 200 && dist < 500){
            lcd_cursor(2,1);
			lcd_string("   ");
            lcd_cursor(1,13);
			lcd_string("far ");
        }
        if(dist > 500 && dist < 800){

            lcd_cursor(1,13);
			lcd_string("very");
			lcd_cursor(2,1);
			lcd_string("far");
        }

	}

}
