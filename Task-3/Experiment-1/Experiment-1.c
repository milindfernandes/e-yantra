/*
* File name: Experiment-1
* Description: This experiment is a part of Task 3. It is aimed to get you familiar with the LCD interfacing.
* This experiment involves writing a code to display a given string of alpha numeric characters on the LCD.
  Author: e-Yantra Team
*/

/* LCD Connections

		  	 LCD	 Microcontroller Pins
 			  RS  --> PC0
			  RW  --> PC1
			  EN  --> PC2
			  DB7 --> PC7
			  DB6 --> PC6
			  DB5 --> PC5
			  DB4 --> PC4
*/


#define __OPTIMIZE__ -O0			// set optimization level to 0. Change only if you know what it does 				
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 14745600
#include <util/delay.h>
#include "lcd.h"		// user-defined header file - it is included in project folder

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
Example Call: port_init() 
*/

void port_init()
	{
	 
	 DDRC= DDRC | 0xF7 ; // All Port C pins except Pin no. 4 i.e(PC3) have to be set as output.

	 PORTC= PORTC & 0x08; // Write suitable value in the PORT C register to make initial values to be "0" 
	 		  //Set initial value as "0" on all pins except Pin no.4 (PC3)
	 
	}


/*
* Function Name:lcd_set_4bit
* Input:none
* Output: none
* Logic: Initialization sequence of LCD in 4-bit mode 
* Example call: lcd_set_4bit();

Note : This function has been defined in the C file "lcd_interfacing.c". 
*/


/*
* Function Name: lcd_wr_command
* Input: unsigned char cmd 
* Output: none
* Logic: Splits command — splits into two 4 bit nibbles and sends them to LCD
* Example call: lcd_wr_command(command in hex);

Note : This function has been defined in the C file "lcd_interfacing.c".
*/


/*
* Function Name: lcd_wr_data
* Input: signed char 
* Output: none
* Logic: Splits data into two 4 bit nibbles and sends them to LCD
* Example call: lcd_wr_data(ASCII value of data);

Note : This function has been defined in the C file "lcd_interfacing.c".
*/


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
* Function Name: main()
* Input: none
* Output: none
* Logic: Initialize LCD and display message on LCD  
*/
int main(void)
	{	
	port_init();
	lcd_set_4bit();
	lcd_init();

	
	lcd_wr_command(0x80);	//Write command for 1st line 4th column. Cursor will be set at home position
	lcd_cursor(1,4);
	////Send ASCII code one by one for message to be displayed on line one/////////////
	lcd_wr_data(84); //Write ASCII code for "T" 
	lcd_wr_data(66); //Write ASCII code for "B"
	lcd_wr_data(84); //Write ASCII code for "T"

    ////////////////////////////////////////////////////////////////////
	
	lcd_wr_command(0xC0);	//Write command to move cursor to 2nd line 2nd column. 
	lcd_cursor(2,2);
	////Send ASCII code one by one for massage for line one/////////////
	lcd_wr_data(101); //Write ASCII code for "e" 
	lcd_wr_data(45); //Write ASCII code for "-"
	lcd_wr_data(121); //Write ASCII code for "Y"	
	lcd_wr_data(97); //Write ASCII code for "a" 
	lcd_wr_data(110); //Write ASCII code for "n"
	lcd_wr_data(116); //Write ASCII code for "t"
	lcd_wr_data(114); //Write ASCII code for "r" 
	lcd_wr_data(97); //Write ASCII code for "a"
	////////////////////////////////////////////////////////////////////
	
	while(1);  // Infinite loop. To halt the execution 
	
	}
