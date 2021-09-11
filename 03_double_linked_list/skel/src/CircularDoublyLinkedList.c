#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

doubly_linked_list_t*
dll_create(unsigned int data_size) {
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
    DIE(list == NULL, "malloc failed");

    list->head = NULL;
    list->size = 0;
    list->data_size = data_size;

    return list;
}

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n) {
    dll_node_t *current = list->head;

    unsigned int count = 0;

    if (n >= list->size)
        n = n % list->size;

    while (count < n) {
        count++;
        current = current->next;
    }

    return current;
}

void
dll_add_nth_node(doubly_linked_list_t* list,
                unsigned int n, const void* data) {
    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    DIE(new_node == NULL, "malloc failed");

    new_node->data = malloc(list->data_size);
    DIE(new_node->data == NULL, "malloc failed");
    memcpy(new_node->data, data, list->data_size);

    if (list->size == 0) {
        // the list is empty
        list->head = new_node;
        list->head->next = list->head;
        list->head->prev = list->head;
    } else {
        if (n > list->size) {
            n = list->size;
        }

        dll_node_t *current = dll_get_nth_node(list, n);
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;

        if (n == 0) {
            // added the new node at the beginning
            list->head = new_node;
        }
    }

    list->size++;
}

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n) {
    dll_node_t *ptr;

    if (n == 0) {
        // the removed node was the first in the list
        ptr = list->head;
        list->head = ptr->next;
        list->head->prev = ptr->prev;
        ptr->prev->next = list->head;
    } else {
        if (n > list->size) {
            n = list->size - 1;
        }

        dll_node_t *current = dll_get_nth_node(list, n);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        ptr = current;
    }

    list->size--;

    return ptr;
}

unsigned int
dll_get_size(doubly_linked_list_t* list) {
    return list->size;
}

void
dll_free(doubly_linked_list_t** pp_list) {
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

void
dll_print_int_list(doubly_linked_list_t* list) {
    dll_node_t* current;
    
    current = list->head;

    do {
        printf("%d ", *(int*)current->data);
        current = current->next;
    } while(current != list->head);

    printf("\n");
}

void
dll_print_string_list(doubly_linked_list_t* list) {
    dll_node_t* current;
    
    current = list->head;

    do {
        printf("%s ", (char*)current->data);
        current = current->next;
    } while(current != list->head);

    printf("\n");
}

void
dll_print_ints_left_circular(dll_node_t* start) {
    dll_node_t *current = start;

    do {
        printf("%d ", *(int*)current->data);
        current = current->prev;
    } while(current != start);
    

    printf("\n");
}

void
dll_print_ints_right_circular(dll_node_t* start) {
    dll_node_t *current = start;

    do {
        printf("%d ", *(int*)current->data);
        current = current->next;
    } while(current != start);
    
    printf("\n");
}
