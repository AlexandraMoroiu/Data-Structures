#include "LinkedList.h"
#include "LinkedList.c"
#include <stdio.h>
#include <stdlib.h>

// adds the number's digits in the list in reverse order
linked_list_t* make_list(linked_list_t* list, int n) {
	int cif;
	while(n != 0) {
		cif = n % 10;
		n = n/10;
		ll_add_nth_node(list, list->size, &cif);
	}

	return list;
}

// returns the sum of 2 numbers as a list
linked_list_t* list_sum(linked_list_t *list1, linked_list_t *list2) {
	linked_list_t *list3 = ll_create(sizeof(int));

	ll_node_t *curr1 = list1->head;
	ll_node_t *curr2 = list2->head;
	
	int sum, carry = 0;
	void *ptr_sum = &sum, *ptr_carry = &carry;

	while(curr1 != NULL || curr2 != NULL) {
		sum = carry;
		if(curr2 != NULL) {
			sum += *(int*)curr2->data;
			curr2 = curr2->next;
		} 
		if(curr1 != NULL) {
			sum += *(int*)curr1->data;
			curr1 = curr1->next;
		}

		if(sum >= 10) {
			carry = 1;
		} else {
			carry = 0;
		}

		sum = sum % 10;

		ll_add_nth_node(list3, list3->size, ptr_sum);

		// reached the end
		if(!curr1 && !curr2 && carry > 0) {
			ll_add_nth_node(list3, list3->size, ptr_carry);
		}
	}

	return list3;

}

int main() {

	int n;
	printf("1st number: ");
	scanf("%d", &n);

	linked_list_t* list1 = ll_create(sizeof(int));

	list1 = make_list(list1, n);

	ll_print_int(list1);

	printf("2nd number: ");
	scanf("%d", &n);

	linked_list_t* list2 = ll_create(sizeof(int));

	list2 = make_list(list2, n);

	ll_print_int(list2);

	printf("Result: \n");

	linked_list_t *list3 = list_sum(list1, list2);

	ll_print_int(list3);

	ll_free(&list1);
	ll_free(&list2);
	ll_free(&list3);

	return 0;
}