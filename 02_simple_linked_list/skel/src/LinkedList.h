#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_

typedef struct ll_node_t ll_node_t;
struct ll_node_t
{
    void* data;
    ll_node_t* next;
};

typedef struct linked_list_t linked_list_t;
struct linked_list_t
{
    ll_node_t* head;
    unsigned int data_size;
    unsigned int size;
};

/**
 * ll_create() - Allocates memory for the list
 * @arg1: Node's data size
 * 
 * Return: Newly created list
 */
linked_list_t*
ll_create(unsigned int data_size);

/**
 * ll_add_nth_node() - Adds new node in the list
 * @arg1: Linked list
 * @arg2: New node's position in the list
 * @arg3: New node's data
 */
void
ll_add_nth_node(linked_list_t* list, unsigned int n, const void* data);

/**
 * ll_remove_nth_node() - Removes node from the list
 * @arg1: Linked list
 * @arg2: Node's position in the list
 *
 * Return: Pointer to the removed node
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n);

unsigned int
ll_get_size(linked_list_t* list);

/**
 * ll_free() - Frees the memory occupied by the entire linked list
 * @arg1: Pointer to the linked list
 */
void
ll_free(linked_list_t** pp_list);

void
ll_print_int(linked_list_t* list);

void
ll_print_string(linked_list_t* list);

#endif /* __LINKED_LIST_H_ */
