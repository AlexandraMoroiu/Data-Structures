#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
	linked_list_t *list = malloc(sizeof(linked_list_t));
	DIE(list == NULL, "malloc failed");

	list->head = NULL;
	list->size = 0;
	list->data_size = data_size;

	return list;
}

void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
	ll_node_t *new_node;
	unsigned int count = 0;

	new_node = malloc(sizeof(ll_node_t));
	DIE(new_node == NULL, "malloc failed");

	new_node->data = malloc(list->data_size);
	DIE(new_node->data == NULL, "malloc failed");

	memcpy(new_node->data, new_data, list->data_size);

	if(list->size == 0 || n == 0) {
		/* list is empty / add at the beginning */
		new_node->next = list->head;
		list->head = new_node;
	} else {
		ll_node_t *current;

		if(list->size < n) {
			n = list->size;
		}

		current = list->head;

		while(count < n - 1) {
			count++;
			current = current->next;
		}

		new_node->next = current->next;
		current->next = new_node;
	}
	list->size++;
}

ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
	ll_node_t *ptr;
	unsigned int count = 0;

	if(n == 0) {

		ptr = list->head;
		list->head = ptr->next;
		
	} else {
		ll_node_t *current;

		if(list->size - 1 < n) {
			n = list->size - 1;
		}

		current = list->head;

		while(count < n - 1) {
			count++;
			current = current->next;
		}

		ptr = current->next;
		current->next = current->next->next;
	}

	list->size--;

	return ptr;
}

unsigned int
ll_get_size(linked_list_t* list)
{
	
	return list->size;
}

void
ll_free(linked_list_t** pp_list)
{
	ll_node_t *tmp;

	while((*pp_list)->head != NULL) {
		tmp = (*pp_list)->head;
		(*pp_list)->head = (*pp_list)->head->next;

		free(tmp->data);
		tmp->data = NULL;

		free(tmp);
		tmp = NULL;
	}

	free(*pp_list);
	*pp_list = NULL;
}

void
ll_print_int(linked_list_t* list)
{
	ll_node_t* current;
	
	current = list->head;

	while(current != NULL) {
		printf("%d ", *(int*)current->data);
		current = current->next;
	}

	printf("\n");
}

void
ll_print_string(linked_list_t* list)
{
	ll_node_t* current;
	
	current = list->head;

	while(current != NULL) {
		printf("%s ", (char*)current->data);
		current = current->next;
	}

	printf("\n");
}
