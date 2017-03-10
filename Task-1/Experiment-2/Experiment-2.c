/*
* Filename: Experiment-1
* Description: This experiment is part of Task-1. It is aimed to get you familiar with the basic constructs of C-programming such as variables, 
loops, codition checking. This  will be helpful when you start programming the robot.
* Author: e-Yantra Team
* Functions: main(), odd_even().
*/


/*
* Preprocessor declarations
*/
//#define __OPTIMIZE__ -O0 // set optimization level to 0. Change only if you know what it does 
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


/*
*	Global Variable Declaration
*/
 // Declare any global variable if you require here


/*
* Function Name: odd_even
* Input: number (number will be a whole number)

* Output:'Y'(if number is even) or 'N'(if number is odd)

* Logic: WRITE YOUR ALGORITHIM HERE

* Example Call: odd_even(50)	-- find if number is odd or even. if even then store 'Y' in result variable.
                odd_even(11)    -- find if number is odd or even. if odd then store 'N' in result variable.
*/


char odd_even(unsigned int number)

{
	
	// Define a variable result. Give a suitable variable data type.
		/***********************************************************************
				WRITE YOUR CODE HERE. Please comment the code.
	
	************************************************************************/
	char result;	// Define result as char datatype
	if(number % 2 ==0 )	// Find modulo 2 of the number, if 0 it is a even number
	{
		result = 'Y';	
	}
	
	else				// else it is a odd number, remainder 1
	{
		result = 'N';	
	}
	return result;  // Do not change the return
}

/*
* Function Name: main()
* Input: none
* Output: none
* Logic: Main function calls function odd_even(), which will find if the given number is an odd or even number*/

int main (void)
{
	unsigned char result_value;

	result_value = odd_even(9); // sample function call (Example: for 9 
								//it should return 'N' & for 100 it should return 'Y')
    result_value = odd_even(30);
}
