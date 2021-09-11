#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size) {
	queue_t *q = malloc(sizeof(queue_t));
	DIE(q == NULL, "malloc failed");

	q->max_size = max_size;
	q->size = 0;
	q->data_size = data_size;
	q->read_idx = 0;
	q->write_idx = 0;

	q->buff = malloc(max_size * sizeof(void *));
	DIE(q->buff == NULL, "malloc failed");

	return q;
}

unsigned int
q_get_size(queue_t *q) {
	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q) {
	DIE(q == NULL, "null queue");

	if(q->size)
		return 0;
	return 1;
}

void *
q_front(queue_t *q) {
	DIE(q == NULL, "null queue");
	DIE(q->buff == NULL, "null array");

	return q->buff[q->read_idx];
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q) {
	DIE(q == NULL, "null queue");

	if(q->size == 0) {
		// coada e goala
		return false;
	}

	free(q_front(q));

	q->read_idx++;
	if(q->read_idx >= q->max_size) {
		q->read_idx = q->read_idx % q->max_size;
	}

	q->size--;

	return true;
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data) {
	DIE(q == NULL, "null queue");

	if(q->size == q->max_size) {
		// coada e plina
		return false;
	}

	q->buff[q->write_idx] = malloc(q->data_size);
	DIE(q->buff[q->write_idx] == NULL, "malloc failed");
	memcpy(q->buff[q->write_idx], new_data, q->data_size);

	q->write_idx++;
	if(q->write_idx >= q->max_size) {
		q->write_idx = q->write_idx % q->max_size;
	}

	q->size++;

	return true;
}

void
q_clear(queue_t *q) {
	DIE(q == NULL, "null queue");

	while(q->size) {
		q_dequeue(q);
	}
}

void
q_free(queue_t *q) {
	DIE(q == NULL, "null queue");

	q_clear(q);
	free(q->buff);
	free(q);
}
