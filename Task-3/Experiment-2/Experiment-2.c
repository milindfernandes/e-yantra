/*
* File name: Experiment-2
* Author: e-Yantra Team
* Description: This experiment is part of Task-3. It is aimed to get you familiar with the LCD interfacing.
* 			   A counter going from 0 to 25 with a delay of one second has to be displayed on the LCD.
LCD Connections:
 			  LCD	  Microcontroller Pins
 			  RS  --> PC0
			  RW  --> PC1
			  EN  --> PC2
			  DB7 --> PC7
			  DB6 --> PC6
			  DB5 --> PC5
			  DB4 --> PC4

*/
// to avoid new compilers complaining about _delay_ expecting a constant
//#define __DELAY_BACKWARD_COMPATIBLE__  //CodeBlocks 16.01


#define __OPTIMIZE__ -O0			// set optimization level to 0. Change only if you know what it does
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
// to avoid new compilers complaining about _delay_ expecting a constant

/*
*	Global Variable Declaration
*/
 // Declare any global variable if you require here



/*
* Function Name: port_init
* Input: none
* Output: none
* Logic: Code to initialize desired I/O port using IO port registers
		 viz. DDRx and PORTx.
Example Call: port_init();
*/

void port_init()
	{

	 DDRC= DDRC | 0xF7; // All Port C pins except Pin no. 4 i.e(PC3) have to be set as output.

	 PORTC= PORTC & 0x08 ; // Write suitable value in the PORT C register to make initial values to be "0"
	 		  //Set initial value as "0" on all pins except Pin no.4 (PC3)

	}



/*
* Function Name: lcd_init()
* Input: none
* Output: none
* Logic: Initialization of LCD i.e. sets function as 4bit, turns on display and cursor etc.
* Example call: lcd_init();
*/

void lcd_init()
{
	_delay_ms(1);			// delay of 1 millisecond

	lcd_wr_command(0x28);	//Set LCD in 4-bit mode and 2 lines (16 x 2).

	lcd_wr_command(0x01);	// write command to clear display


	lcd_wr_command(0x0F); // write command to turn on display with cursor blinking

	lcd_wr_command(0x06); // auto increment cursor

}

/*
* Function Name: display
* Input: unsigned char val
* Output: none
* Logic: Splits variable val in to tens and unit digit. Convert it in to ASCII code and display it.
* Example call: display(12);
*/
void display (unsigned char val)
	{
	/*
	val is unsigned variable with range of 0-255
	This variable can not be directly converted in to ASCII code.
	To convert this variable in ASCII first split this variable in to tens and unit digits and then convert in to ASCII by adding 0x30
	To split in to tens and unit digits, division and modulo function can be used. Reference code is given below.
	*/
	unsigned char temp;
	temp=val/10; 				//This operation will give tens digit
	lcd_wr_command(0xC0);			//Give command for 2nd line first column
	lcd_cursor(2,1);
	lcd_wr_data(temp + 0x30);	//This function will add 0x30 in to temp value to convert ASCII code and will display it.

		//Similarly write code for unit digit
		//Note cursor is set to auto increment so no need to set cursor every time
	temp = val % 10;
	lcd_wr_data(temp + 0x30);
	}


/*
* Function Name: main()
* Input: none
* Output: none
* Logic: Initialize LCD and display message on LCD
*/
int main(void)
	{
	port_init();
	unsigned char i=0;
	lcd_set_4bit();
	lcd_init();
	lcd_wr_command(0x80); //Write command for first line first column. Courser will be set at home position
	lcd_cursor(1,1);
	////Send ASCII code one by one for message to be displayed on line one/////////////
	lcd_wr_data('C'); //Write ASCII code for "C" in "--"
	lcd_wr_data('o');
	lcd_wr_data('u');
	lcd_wr_data('n');
	lcd_wr_data('t');
	lcd_wr_data('e');
	lcd_wr_data('r');
	//repeat the above statement with appropriate ASCII code for displaying "Counter".
	////////////////////////////////////////////////////////////////////
	lcd_wr_command(0xC0);
	lcd_cursor(2,1);
		/*
		Write a program to increment a variable "i"
		Write a for loop to increment "i" from 0 to 25 with a delay of 1 second.
		Display the variable on 2nd line first column of LCD
		*/
		for (i=0;i<=25;i++)
		{
			//write your code here
				display(i);
				_delay_ms(1000);
		}


	}
