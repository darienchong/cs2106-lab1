/*************************************
* Lab 1 Exercise 2
* Name: Darien Chong
* Student No: A0168214H
* Lab Group: 6
*************************************/

#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

bool debug;
int (*func_list[5])(int);
// write the necessary code to initialize the func_list
// array here, if needed

void update_functions() 
{
	if (debug) {
		printf("[update_functions]: Entered successfully.\n");
	}

	func_list[0] = add_one;
	func_list[1] = add_two;
	func_list[2] = multiply_five;
	func_list[3] = square;
	func_list[4] = cube;
	
	
	if (debug) {
		printf("[update_functions]: Exiting.\n");
	}
	return;
}
