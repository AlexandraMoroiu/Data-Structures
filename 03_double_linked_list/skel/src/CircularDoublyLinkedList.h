#ifndef __CIRCULAR_DOUBLY_LINKED_LIST_H_
#define __CIRCULAR_DOUBLY_LINKED_LIST_H_

typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data;
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

/**
 * dll_create() - Allocates memory for the list
 * @arg1: Node's data size
 * 
 * Return: Newly created circular list
 */
doubly_linked_list_t*
dll_create(unsigned int data_size);

/**
 * dll_get_nth_node() - Searches node in the list
 * @arg1: Doubly linked list
 * @arg2: Node's position in the list
 *
 * Return: Wanted node
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n);

/**
 * dll_add_nth_node() - Adds new node in the list
 * @arg1: Linked list
 * @arg2: New node's position in the list
 * @arg3: New node's data
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data);

/**
 * dll_remove_nth_node() - Removes node from the list
 * @arg1: Linked list
 * @arg2: Node's position in the list
 *
 * Return: Pointer to the removed node
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n);

unsigned int
dll_get_size(doubly_linked_list_t* list);

/**
 * dll_free() - Frees the memory occupied by the entire list
 * @arg1: Pointer to the doubly linked list
 */
void
dll_free(doubly_linked_list_t** pp_list);

void
dll_print_int_list(doubly_linked_list_t* list);

void
dll_print_string_list(doubly_linked_list_t* list);

void
dll_print_ints_left_circular(dll_node_t* start);

void
dll_print_ints_right_circular(dll_node_t* start);
#endif /* __CIRCULAR_DOUBLY_LINKED_LIST_H_*/
