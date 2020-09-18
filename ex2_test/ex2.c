/*************************************
* Lab 1 Exercise 2
* Name: Darien Chong
* Student No: A0168214H
* Lab Group: 6
*************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"
#include "function_pointers.h"

// the runner is empty now! Modify it to fulfill the requirements of the
// exercise. You can use ex1.c as a template

// macros
#define SUM_LIST 0
#define INSERT_FROM_HEAD_AT 1
#define INSERT_FROM_TAIL_AT 2
#define DELETE_FROM_HEAD_AT 3
#define DELETE_FROM_TAIL_AT 4
#define RESET_LIST 5
#define MAP 6

bool debug = false;

int read_next_integer_from(FILE *stream, int *buffer);
void run_instruction(list *lst, int instr, FILE *stream);

int main(int argc, char **argv)
{
    
    if (argc != 2)
    {
        fprintf(stderr, "Error: expecting 1 argument, %d found\n", argc - 1);
        exit(1);
    }

    // we read in the file name provided as argument
    char *fname = argv[1];

    // updating the array of function pointers
    // do not remove this call 
    // (you may leave the function empty if you do not need it)
    
    update_functions();

    // rest of code logic here
    // Set up empty list
    list *lst = (list *)malloc(sizeof(list));
    lst -> head = NULL;
    lst -> tail = NULL;
	
	// Read in instructions
	FILE *fp;
	fp = fopen(fname, "r");
	
	// We failed to open the file
	if (fp == NULL) {
		fprintf(stderr, "Error: failed to open the file.\n");
		exit(1);
	}
	
	int instr = -1;
	
    while (read_next_integer_from(fp, &instr) == 1) {
   		if (debug) {
   			printf("[ex2:main]: Successfully read in instr = %d\n", instr);
   		}
    	run_instruction(lst, instr, fp);
    }
    
    // Cleanup
    fclose(fp);
    reset_list(lst);
    free(lst);
    
    return 0;
}

// takes an instruction enum and runs the corresponding function
// we assume input always has the right format (no input validation on runner)
void run_instruction(list *lst, int instr, FILE *stream)
{
	if (debug) {
		printf("[run_instruction(lst, %d, stream)]: Entered successfully.\n", instr);
	}

    int index;
    int data;

    switch (instr)
    {
    case SUM_LIST:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `SUM_LIST` case.\n", instr);
		}
        printf("%ld\n", sum_list(lst));
        break;
    case INSERT_FROM_HEAD_AT:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `INSERT_FROM_HEAD_AT` case.\n", instr);
		}
		
        int index_read_check = read_next_integer_from(stream, &index);
        int data_read_check = read_next_integer_from(stream, &data);
        bool is_failed_to_read_params = index_read_check != 1 || data_read_check != 1;
        
        if (debug && is_failed_to_read_params) {
        	printf("[run_instruction(lst, %d, stream)]: Failed to read in either of index or data.\n", instr);
        }
         
        insert_node_from_head_at(lst, index, data);
        break;
    case INSERT_FROM_TAIL_AT:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `INSERT_FROM_TAIL_AT` case.\n", instr);
		}
        index_read_check = read_next_integer_from(stream, &index);
        data_read_check = read_next_integer_from(stream, &data);
        is_failed_to_read_params = index_read_check != 1 || data_read_check != 1;
        
        if (debug && is_failed_to_read_params) {
        	printf("[run_instruction(lst, %d, stream)]: Failed to read in either of index or data.\n", instr);
        }
        
        insert_node_from_tail_at(lst, index, data);
        break;
    case DELETE_FROM_HEAD_AT:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `DELETE_FROM_HEAD_AT` case.\n", instr);
		}
		
        index_read_check = read_next_integer_from(stream, &index);
        is_failed_to_read_params = index_read_check != 1;
        
        if (debug && is_failed_to_read_params) {
        	printf("[run_instruction(lst, %d, stream)]: Failed to read in index.\n", instr);
        }
        delete_node_from_head_at(lst, index);
        break;
     case DELETE_FROM_TAIL_AT:
     	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `DELETE_FROM_TAIL_AT` case.\n", instr);
		}
        index_read_check = read_next_integer_from(stream, &index);
        is_failed_to_read_params = index_read_check != 1;
        
        if (debug && is_failed_to_read_params) {
        	printf("[run_instruction(lst, %d, stream)]: Failed to read in index.\n", instr);
        }
        delete_node_from_tail_at(lst, index);
        break;   
    case RESET_LIST:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `RESET_LIST` case.\n", instr);
		}
        reset_list(lst);
        break;
    case MAP:
    	if (debug) {
			printf("[run_instruction(lst, %d, stream)]: Entered `MAP` case.\n", instr);
		}
		
   		index_read_check = read_next_integer_from(stream, &index);
        is_failed_to_read_params = index_read_check != 1;
        
        if (debug && is_failed_to_read_params) {
        	printf("[run_instruction(lst, %d, stream)]: Failed to read in index.\n", instr);
        }
    	
    	if (debug) {
    		printf("[run_instruction(lst, %d, stream)]: index = %d\n", instr, index);
    	}
    	
    	int (*func) (int) = func_list[index];
    	
    	if (debug) {
    		printf("[run_instruction(lst, %d, stream)]: func's address = %p\n", instr, &func);
    	}
    	map(lst, func);
    }
}

// Reads the next integer in the file to the buffer.
// Returns the number of items read.
int read_next_integer_from(FILE *stream, int *buffer) {
	return fscanf(stream, "%d", buffer);
}
