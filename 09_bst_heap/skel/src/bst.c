/**
 * SD, 2021
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Binary Search Tree implementation
 */

#include "bst.h"
#include "utils.h"

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t *__bst_node_create(void *data, size_t data_size) {
	bst_node_t *bst_node;  

	bst_node = malloc(sizeof(*bst_node));

	DIE(bst_node == NULL, "bst_node malloc");

	bst_node->left = bst_node->right = NULL;

	bst_node->data = malloc(data_size);
	DIE(bst_node->data == NULL, "bst_node->data malloc");
	memcpy(bst_node->data, data, data_size);

	return bst_node;
}

bst_tree_t *bst_tree_create(size_t data_size,
							int (*cmp_f)(const void *, const void *)) {
	bst_tree_t *bst_tree;

	bst_tree = malloc(sizeof(*bst_tree));
	DIE(bst_tree == NULL, "bst_tree malloc");

	bst_tree->root  = NULL;
	bst_tree->data_size = data_size;
	bst_tree->cmp   = cmp_f;

	return bst_tree;
}

void bst_tree_insert(bst_tree_t *bst_tree, void *data) {
	int rc;
	bst_node_t *root    = bst_tree->root;
	bst_node_t *parent  = NULL;
	bst_node_t *node    = __bst_node_create(data, bst_tree->data_size);

	if(root == NULL) {
		bst_tree->root = node;
		return;
	}

	parent = root;

	while(1) {
		rc = bst_tree->cmp(data, parent->data);
		/* data is smaller than parent node's */
		if(rc < 0) {
			if(parent->left == NULL) {
				parent->left = node;
				break;
			}
			parent = parent->left;
			continue;
		}

		/* data is bigger than parent node's */
		if(rc > 0) {
			if(parent->right == NULL) {
				parent->right = node;
				break;
			}
			parent = parent->right;
			continue;
		}

		/* the node was already inserted */
		if(!rc) {
			break;
		}
	}
}

/* finds the smallest node from the right subtree */
static bst_node_t *min_right(bst_node_t *node) {
	bst_node_t *current = node;
	while(current && current->left != NULL) {
		current = current->left;
	}

	return current;
}

/* finds the biggest node from the left subtree */
static bst_node_t *max_left(bst_node_t *node) {
	bst_node_t *current = node;
	while(current && current->right != NULL) {
		current = current->right;
	}

	return current;
}

/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
									void *data, size_t data_size,
									int (*cmp)(const void *, const void *)) {
	int rc;
	bst_node_t *tmp;

	if (!bst_node)
		return bst_node;

	rc = cmp(data, bst_node->data);

	if (rc < 0) {
		/* the node is in the left subtree */
		bst_node->left = __bst_tree_remove(bst_node->left, data,
											data_size, cmp);
	} else if (rc > 0) {
		/* the node is in the right subtree */
		bst_node->right = __bst_tree_remove(bst_node->right, data,
											data_size, cmp);
	} else {
		/* the node is a leaf or has one child */
		if(bst_node->left == NULL && bst_node->right == NULL) {
			tmp = bst_node;
			bst_node = NULL;
			free(tmp->data);
			free(tmp);
		} else if(bst_node->left == NULL) {
			tmp = bst_node;
			bst_node = bst_node->right;
			free(tmp->data);
			free(tmp);
		} else if(bst_node->right == NULL) {
			tmp = bst_node;
			bst_node = bst_node->left;
			free(tmp->data);
			free(tmp);
		} else {
			/* the node has 2 children */

			/* find the leftmost node */
			bst_node_t *tmp_left = max_left(bst_node->left);
			/* find the rightmost node */
			bst_node_t *tmp_right = min_right(bst_node->right);

			int rc_left = cmp(bst_node->data, tmp_left->data);
			int rc_right = cmp(tmp_right->data, bst_node->data);

			if(rc_right <= rc_left) {
				memcpy(bst_node->data, tmp_right->data, data_size);
				bst_node->right = __bst_tree_remove(bst_node->right,
													tmp_right->data,
													data_size, cmp);
			} else {
				memcpy(bst_node->data, tmp_left->data, data_size);
				bst_node->left = __bst_tree_remove(bst_node->left,
													tmp_left->data,
													data_size, cmp);
			}
		}
	}

	return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, void *data) {
	bst_tree->root = __bst_tree_remove(bst_tree->root, data,
									   bst_tree->data_size,
									   bst_tree->cmp);
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free(bst_node_t *bst_node, void (*free_data)(void *)) {
	if (!bst_node)
		return;

	__bst_tree_free(bst_node->left, free_data);
	__bst_tree_free(bst_node->right, free_data);
	free(bst_node->data);
	free(bst_node);
}

void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *)) {
	__bst_tree_free(bst_tree->root, free_data);
	free(bst_tree);
}

static void
__bst_tree_print_inorder(bst_node_t* bst_node, void (*print_data)(void*)) {
	if (!bst_node)
		return;
		
	__bst_tree_print_inorder(bst_node->left, print_data);
	print_data(bst_node->data);
	__bst_tree_print_inorder(bst_node->right, print_data);
}

void
bst_tree_print_inorder(bst_tree_t* bst_tree, void (*print_data)(void*)) {
	__bst_tree_print_inorder(bst_tree->root, print_data);
}
