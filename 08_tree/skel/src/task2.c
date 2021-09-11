/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <subarbore cu suma nodurilor maxima>
 */
#include <stdio.h>
#include <limits.h>

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree) {
    int i, N, data;

    scanf("%d", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d", &data);
        b_tree_insert(b_tree, &data);
    }
}

int max(int a, int b) {
	if(a > b) {
		return a;
	}

	return b;
}

int find_max(b_node_t *node, int *current_max, b_node_t **subtree_root) {
	// am ajuns la finalul subarborelui
	if(node == NULL) {
		return 0;
	}

	int parent_sum = *(int *)node->data;
	int l_sum = find_max(node->left, current_max, subtree_root);
	int r_sum = find_max(node->right, current_max, subtree_root);

	int max_sum = max(l_sum + r_sum + parent_sum, max(l_sum, r_sum));

	// nodul fusese frunza si avea stocata o valore negativa
	if(!l_sum && !r_sum && parent_sum < 0) {
		max_sum = parent_sum;
	}

	if(max_sum > *current_max) {
		*current_max = max_sum;
		*subtree_root = node;
	}

	return max_sum;
}

int main(void) {
    b_tree_t *binary_tree;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);

    int current_max = INT_MIN;

    b_node_t *subtree_root;
    current_max = find_max(binary_tree->root, &current_max, &subtree_root);

    printf("Subtree root and max sum: ");
    printf("%d %d\n", *(int *)subtree_root->data, current_max);

    exit(EXIT_FAILURE);
}
