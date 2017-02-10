/*
* Filename: Experiment-2
* Description: This experiment is a part of Task 2. It is aimed at getting you familiar with I/O interfacing by writing a code to sense pressing of a push button switch.
* Author: e-Yantra Team
* Functions: main(),port_init(),led_on(),led_off().
*/


// Note : You may write more functions depending on requirement.



#include <avr/io.h>
#include <stdio.h>
#define F_CPU 14745600
#include <util/delay.h>


/*Function name: port_init
Input: none
Output: none
Logic: Code to initialize desired I/O ports
*/

void port_init(void)
{
	// write your code here
DDRJ = DDRJ | 0xF0;  // set upper nibble as output
PORTJ = 0x00;	// initially all led off
DDRE = DDRE & 0x7F; // Set pin7 of PortE as Input, starts from pin 0!!
PORTE = PORTE | 0x80; // Set Pin7 pullup high
}
/*Function name: led_on
Input: none
Output: none
Logic: Code to turn on bar led
*/
void led_on(void)
{
	//write your code here
	PORTJ = PORTJ | 0xF0;
}

/*Function name: led_off
Input: none
Output: none
Logic: Code to turn off bar led
*/
void led_off(void)
{
	// write your code here
	PORTJ = PORTJ & 0x0F;
}

/*Function name: main
Input: none
Output: none
Logic: Program Execution starts from this function. Your code can have only one main function.
*/

int main()
{
	//write your code here
	port_init();
	while(1){
	if((PINE & 0x80)== 0){
	led_on();
	
	}
	else{
	led_off();
	}
	}
}
