/*************************************
* Lab 1 Exercise 2
* Name: Darien Chong
* Student No: A0168214H
* Lab Group: 6
*************************************/

#include "functions.h"

// write the necessary code to initialize the func_list
// array here, if needed

void update_functions() 
{
	int (*func_list[5]) (int) = {
		add_one,
		add_two,
		multiply_five,
		square,
		cube
	};

	return;
}
