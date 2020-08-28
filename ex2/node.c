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
#include <ctype.h>
#include "node.h"

// add in your implementation below to the respective functions
// feel free to add any headers you deem fit (although you do not need to)

// Debug flag, enables debug messages.
bool debug;

// Returns the length of the list.
int length(list *lst)
{
	if (debug) {
		printf("  * [length(lst)]: Entered successfully.\n");
	}
	
	if (lst -> head == NULL) {
		return 0;
	}

	int length_recorded = 0;
	struct NODE *current_node = lst -> head;

	while (current_node != NULL) {
		current_node = current_node -> next;
		length_recorded++;
	}
	
	if (debug) {
		printf("  * [length(lst)]: Returning a value of [%d].\n", length_recorded);
	}

	return length_recorded;
}

// Returns the node at the position, starting from the head.
// Exits instantly with an error if it goes beyond the list.
struct NODE* get_node_from_head_at(list *lst, int index) 
{
	if (debug) {
		printf("  * [get_node_from_head_at(lst, %d)]: Entered successfully.\n", index);
	}

	if (index == 0) {
		return lst -> head;
	}

	int current_index = index;
	struct NODE *ptr_current_node = lst -> head;

	while (current_index > 0) {
		if (ptr_current_node == NULL) {
			if (debug) {
				printf("  * [get_node_from_head_at(lst, %d)]: Attempted to retrieve node at index %d from list of length %d\n", index, index, length(lst));
			}
			return NULL; 
		}
		ptr_current_node = ptr_current_node -> next;
		current_index -= 1;
	}
	
	if (debug) {
		printf("  * [get_node_from_head_at(lst, %d)]: Exiting.\n", index);
	}
	return ptr_current_node;
}

// Inserts a node between the two given nodes.
// If any of the neighbours are NULL, then this function assumes that the node 
// is being inserted at some end of the list and will update the list's 
// head and/or tail pointers.
void insert_node_between(list *lst, struct NODE *ptr_node, struct NODE *ptr_prev, struct NODE *ptr_next)
{
	if (debug) {
		printf("  * [insert_node_between(...)]: Entered successfully.\n");
	}

	bool is_insertion_at_head = (ptr_prev == NULL);
	bool is_insertion_at_tail = (ptr_next == NULL);
	
	if (debug) {
		printf("  * [insert_node_between(...)]: ptr_prev == NULL: %d\n", is_insertion_at_head);
		printf("  * [insert_node_between(...)]: ptr_next == NULL: %d\n", is_insertion_at_tail);
	}

	// Insertion at head
	// Assumes that `next` == `lst -> head`
	if (is_insertion_at_head) {
		lst -> head = ptr_node;
	}

	// Insertion at tail
	// Assumes that `prev` == `lst -> tail`
	if (is_insertion_at_tail) {
		lst -> tail = ptr_node;
	}

	// Insertion into interior of list
	ptr_node -> prev = ptr_prev;
	ptr_node -> next = ptr_next;
	
	if (debug) {
		printf("  * [insert_node_between(...)]: Successfully assigned ptr_node -> prev, next.\n");
	}
	
	if (!is_insertion_at_tail) {
		ptr_next -> prev = ptr_node;
		
		if (debug) {
			printf("  * [insert_node_between(...)]: Successfully assigned ptr_next -> prev.\n");
		}
	}

	if (!is_insertion_at_head) {
		ptr_prev -> next = ptr_node;
		
		if (debug) {
			printf("  * [insert_node_between(...)]: Successfully assigned ptr_prev -> next.\n");
		}
	}
	
	if (debug) {
		printf("  * [insert_node_between(...)]: Exiting.\n");
	}

	return;
}

// Creates a new node and allocates memory for it.
struct NODE* create_new_node(int data, struct NODE *prev, struct NODE *next) {
	if (debug) {
		printf("  * [create_new_node(%d, prev, next)]: Entered successfully.\n", data);
	}

	struct NODE *new_node = malloc(sizeof(struct NODE));
	new_node -> data = data;
	new_node -> prev = prev;
	new_node -> next = next;

	return new_node;
}

// inserts a new node with data value at index (counting from the front
// starting at 0)
void insert_node_from_head_at(list *lst, int index, int data)
{
	if (debug) {
		printf("  [insert_node_from_head_at(lst, %d, %d)]: Entered successfully.\n", index, data);
	}
	
	struct NODE *ptr_new_node = create_new_node(data, NULL, NULL);	
	bool is_empty_list = (lst -> head == NULL);
	
	if (is_empty_list) {
		lst -> head = ptr_new_node;
		lst -> tail = ptr_new_node;
		return;
	}

	if (index == 0) {
		if (debug) {
			printf("  [insert_node_from_head_at(lst, %d, %d)]: Entered `index == 0` case.\n", index, data);
		}
	
		insert_node_between(lst, ptr_new_node, NULL, lst -> head);
		
		if (debug) {
			printf("  [insert_node_from_head_at(lst, %d, %d)]: Exiting `index == 0` case.\n", index, data);
		}
		return;
	}

	struct NODE *ptr_prev_node = get_node_from_head_at(lst, index - 1);
	struct NODE *ptr_next_node = ptr_prev_node -> next;

	insert_node_between(lst, ptr_new_node, ptr_prev_node, ptr_next_node);	
	
	if (debug) {
		printf("  [insert_node_from_head_at(lst, %d, %d)]: Exiting.\n", index, data);
	}
	return;
}

// inserts a new node with data value at index (counting from the back
// starting at 0)
void insert_node_from_tail_at(list *lst, int index, int data)
{
	if (debug) {
		printf("  [insert_node_from_tail_at(lst, %d, %d)]: Entered successfully.\n", index, data);
	}
	struct NODE *ptr_new_node = create_new_node(data, NULL, NULL);
	int list_length = length(lst);

	// Handle any corner cases first
	if (lst -> tail == NULL) {
		lst -> head = ptr_new_node;
		lst -> tail = ptr_new_node;
		return;
	}
	
	// This means we append to the tail
	if (index == 0) {
		if (debug) {
			printf("  [insert_node_from_tail_at(lst, %d, %d)]: Entering `index == 0` case.\n", index, data);
		}

		free(ptr_new_node);
		
		if (debug) {
			printf("  [insert_node_from_tail_at(lst, %d, %d)]: Successfully freed new node.\n", index, data);
		}

		insert_node_from_head_at(lst, list_length, data);
		return;
	}

	insert_node_from_head_at(lst, list_length - index, data);
	return;
}

// deletes node at index counting from the front (starting from 0)
// note: index is guaranteed to be valid
void delete_node_from_head_at(list *lst, int index)
{
	if (debug) {
		printf("  [delete_node_from_head_at(lst, %d)]: Entered successfully.\n", index);
	}
	
	if (lst -> head == NULL || lst -> tail == NULL) {
		printf("[delete_node_from_head_at(lst, %d)]: Empty list detected, exiting.\n", index);
		return;
	}
	
	// We are guaranteed that the list will not be empty, so we can safely
	// do this.
	bool is_list_singleton = (lst -> head -> next == NULL || lst -> tail -> prev == NULL);
	bool is_deleting_head = (index == 0);

	// Corner case, we delete the last node in the list
	if (is_list_singleton) {
		struct NODE *ptr_node_to_free = lst -> head;
		lst -> head = NULL;
		lst -> tail = NULL;

		free(ptr_node_to_free);
		return;
	}

	if (is_deleting_head) {
		struct NODE *ptr_node_to_free = lst -> head;
		
		lst -> head = ptr_node_to_free -> next;
		ptr_node_to_free -> next -> prev = NULL;
		ptr_node_to_free -> next = NULL;

		free(ptr_node_to_free);
		return;
	}
	
	// We call this here so that we don't incur a penalty
	// if we don't reach this branch.
	bool is_deleting_tail = (index == length(lst) - 1);

	if (is_deleting_tail) {
		struct NODE *ptr_node_to_free = lst -> tail;

		lst -> tail = ptr_node_to_free -> prev;
		ptr_node_to_free -> prev -> next = NULL;
		ptr_node_to_free -> prev = NULL;

		free(ptr_node_to_free);
		return;
	}

	// Now we are guaranteed that we are deleting some node in the interior
	// of the list.
	struct NODE *ptr_node_to_free = get_node_from_head_at(lst, index);
	struct NODE *ptr_node_prev = ptr_node_to_free -> prev;
	struct NODE *ptr_node_next = ptr_node_to_free -> next;

	ptr_node_prev -> next = ptr_node_next;
	ptr_node_next -> prev = ptr_node_prev;

	ptr_node_to_free -> next = NULL;
	ptr_node_to_free -> prev = NULL;

	free(ptr_node_to_free);
	return;
}

// deletes node at index counting from the back (starting from 0)
// note: index is guaranteed to be valid
void delete_node_from_tail_at(list *lst, int index)
{
	if (debug) {
		printf("  [delete_node_from_tail_at(lst, %d)]: Entered successfully.\n", index);
	}
	delete_node_from_head_at(lst, (length(lst) - 1) - index);
}

// resets list to an empty state (no nodes) and frees any allocated memory in
// the process
void reset_list(list *lst)
{
	if (debug) {
		printf("  [reset_list(lst)]: Entered successfully.\n");
	}
	
	bool is_list_empty = lst -> head == NULL || lst -> tail == NULL;
	
	// If list is empty, we are done.
	if (is_list_empty) {
		return;
	}

	struct NODE *ptr_current_node = lst -> head;
	while (ptr_current_node != NULL) {
		struct NODE *ptr_node_to_free = ptr_current_node;
		ptr_current_node = ptr_current_node -> next;

		free(ptr_node_to_free);
	}

	lst -> head = NULL;
	lst -> tail = NULL;
	return;
}

// traverses list and applies func on data values of all elements in the list
void map(list *lst, int (*func)(int))
{
	if (debug) {
		printf("  [map(lst, func)]: Entered successfully.\n");
	}

	bool is_empty_list = lst -> head == NULL || lst -> tail == NULL;
	
	if (is_empty_list) {
		if (debug) {
			printf("  [map(lst, func)]: Entered `is_empty_list` case.\n");
		}
		return;
	}
	
	struct NODE *ptr_current_node = lst -> head;
	while (ptr_current_node != NULL) {
		int current_data = ptr_current_node -> data;
		if (debug) {
			printf("  [map(lst, func)]: current_data = %d\n", current_data);
		}
		ptr_current_node -> data = func(current_data);
		
		if (debug) {
			printf("  [map(lst, func)]: Successfully applied the function to the current data. New data = %d\n", ptr_current_node -> data);
		}
		ptr_current_node = ptr_current_node -> next;
	}

	return;
}

// traverses list and returns the sum of the data values of every node
// in the list
long sum_list(list *lst)
{
	if (debug) {
		printf("  [sum(lst)]: Entered successfully.\n");
	}
	
	long sum = 0L;
	bool is_empty_list = lst -> head == NULL || lst -> tail == NULL;

	if (is_empty_list) {
		return 0L;
	}

	struct NODE *ptr_current_node = lst -> head;
	while (ptr_current_node != NULL) {
		sum += ptr_current_node -> data;
		ptr_current_node = ptr_current_node -> next;
	}

	return sum;
}
