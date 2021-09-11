#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
	doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
	DIE(list == NULL, "malloc failed");

	list->head = NULL;
	list->size = 0;
	list->data_size = data_size;

	return list;
}

/*
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	dll_node_t *current = list->head;

	unsigned int count = 0;

	if(n >= list->size)
		n = list->size;

	while(count < n) {
		count++;
		current = current->next;
	}

	return current;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
	dll_node_t *new_node = malloc(sizeof(dll_node_t));
	DIE(new_node == NULL, "malloc failed");

	new_node->data = malloc(list->data_size);
	DIE(new_node->data == NULL, "malloc failed");
	memcpy(new_node->data, data, list->data_size);

	new_node->next = NULL;
	new_node->prev = NULL;

	if(list->size == 0 || n == 0) {
		/* lista e goala / vreau sa adaug la inceput */
		new_node->next = list->head;
		new_node->prev = NULL;
		list->head = new_node;
	} else {
		dll_node_t *current = dll_get_nth_node(list, n - 1);
		new_node->prev = current;
		new_node->next = current->next;
		current->next = new_node;
	}

	list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	/* TODO */
	dll_node_t *ptr;

	if(n == 0) {
		ptr = list->head;
		list->head = ptr->next;
	} else {
		dll_node_t *current = dll_get_nth_node(list, n - 1);
		printf("totul bine: %d\n", *(int*)current->data);
		ptr = current->next;

		if(n >= list->size - 1) {
			current->next = NULL;
		} else {
			current->next = ptr->next;
			ptr->next->prev = current;
		}
	}

	list->size--;

	return ptr;
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */

unsigned int
dll_get_size(doubly_linked_list_t* list)
{
	return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
	/* TODO */
	dll_node_t *tmp;

	while((*pp_list)->size) {
		tmp = (*pp_list)->head;
		(*pp_list)->head = (*pp_list)->head->next;

		free(tmp->data);
		tmp->data = NULL;

		free(tmp);
		tmp = NULL;

		(*pp_list)->size--;
	}

	free(*pp_list);
	*pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
	dll_node_t* current;
	
	current = list->head;

	while(current != NULL) {
		printf("%d ", *(int*)current->data);
		current = current->next;
	}

	printf("\n");

}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	dll_node_t* current;
	
	current = list->head;

	while(current != NULL) {
		printf("%s ", (char*)current->data);
		current = current->next;
	}

	printf("\n");
}

