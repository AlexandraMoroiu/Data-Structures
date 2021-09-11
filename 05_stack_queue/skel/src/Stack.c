#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

stack_t *
st_create(unsigned int data_size) {
	stack_t *st = malloc(sizeof(stack_t));
	DIE(st == NULL, "malloc failed");

	st->list = ll_create(data_size);
	st->list->size = 0;
	return st;
}

unsigned int
st_get_size(stack_t *st) {
	DIE(st == NULL, "null stack");

	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st) {
	DIE(st == NULL, "null stack");

	if(st->list->size)
		return 0;
	return 1;
}

void *
st_peek(stack_t *st) {
	DIE(st == NULL, "null stack");

	ll_node_t *node = st->list->head;
	return node->data;
}

void
st_pop(stack_t *st) {
	DIE(st == NULL, "null stack");

	ll_node_t *node = ll_remove_nth_node(st->list, 0);
	free(node->data);
	free(node);
}

void
st_push(stack_t *st, void *new_data) {	
	DIE(st == NULL, "null stack");

	// am considerat primul elem din lista ca fiind varful stivei
	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st) {
	DIE(st == NULL, "null stack");

	ll_node_t *node;

	while (st->list->size) {
		st_pop(st);
	}
}

void
st_free(stack_t *st) {
	DIE(st == NULL, "null stack");
	
	st_clear(st);
	free(st->list);
	free(st);
}
