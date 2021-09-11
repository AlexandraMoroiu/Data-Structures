#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"
#include "DoublyLinkedList.c"

void add_middle_node(dll_node_t **head, int data) {

	dll_node_t *new_node = malloc(sizeof(dll_node_t));
	DIE(new_node == NULL, "malloc failed");

	new_node->data = malloc(sizeof(int));
	DIE(new_node->data == NULL, "malloc failed");
	memcpy(new_node->data, &data, sizeof(int));
	
	if(*head == NULL) {
		/* lista is empty */
		*head = new_node;
	} else if( (*head)->next == NULL) {
		/* list has 1 element */
		(*head)->prev = new_node;
		new_node->next = *head;
		*head = new_node;
	} else {
		dll_node_t *normal = *head;
		dll_node_t *quick = (*head)->next;

		while(1) {
			normal = normal->next;
			if(quick == NULL || quick->next == NULL || quick->next->next == NULL)
				break;
			quick = quick->next->next;
		}

		new_node->next = normal;
		new_node->prev = normal->prev;

		normal->prev->next = new_node;
		normal->prev = new_node;

	}
}

int main() {
	doubly_linked_list_t *list = dll_create(sizeof(int));

	int n, i, elem;

	printf("Nr elements list: ");
	scanf("%d", &n);

	for(i = 0; i < n; i++) {
		scanf("%d", &elem);
		dll_add_nth_node(list, i, &elem);
	}

	printf("Add element in the middle: ");
	scanf("%d", &elem);
	add_middle_node(&list->head, elem);

	dll_print_int_list(list);

	dll_free(&list);

}
