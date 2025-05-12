#include "../../../utils/constants.h"
#include "ft_btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_btree *btree_create_node(void *item);
int btree_level_count(t_btree *root);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);
int test7(void);
int test8(void);
int test9(void);
int test10(void);
int test11(void);
int test12(void);
int test13(void);
int test14(void);

// Helpers
t_btree *btree_create_node(void *item) {
	t_btree *node = malloc(sizeof(t_btree));
	if (!node) return NULL;
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void free_tree(t_btree *node) {
	if (!node) return;
	free(node->item);
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

// Main
int main(void) {
	int result = 0;
	if (test1() != 0) result = -1;
	if (test2() != 0) result = -1;
	if (test3() != 0) result = -1;
	if (test4() != 0) result = -1;
	if (test5() != 0) result = -1;
	if (test6() != 0) result = -1;
	if (test7() != 0) result = -1;
	if (test8() != 0) result = -1;
	if (test9() != 0) result = -1;
	if (test10() != 0) result = -1;
	if (test11() != 0) result = -1;
	if (test12() != 0) result = -1;
	if (test13() != 0) result = -1;
	if (test14() != 0) result = -1;
	return result;
}

// Test 1: NULL root (empty tree)
int test1(void) {
	int result = btree_level_count(NULL);
	if (result != 0) {
		printf("    " RED "[1] NULL root failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] NULL root passed\n" DEFAULT);
	return 0;
}

// Test 2: Single node tree
int test2(void) {
	t_btree *r = btree_create_node(strdup("A"));
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 1) {
		printf("    " RED "[2] Single node failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Single node passed\n" DEFAULT);
	return 0;
}

// Test 3: Two levels (root + one child)
int test3(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 2) {
		printf("    " RED "[3] Two levels failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Two levels passed\n" DEFAULT);
	return 0;
}

// Test 4: Full tree, 3 levels
int test4(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->right = btree_create_node(strdup("C"));
	r->left->left = btree_create_node(strdup("D"));
	r->left->right = btree_create_node(strdup("E"));
	r->right->left = btree_create_node(strdup("F"));
	r->right->right = btree_create_node(strdup("G"));
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 3) {
		printf("    " RED "[4] Full tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Full tree passed\n" DEFAULT);
	return 0;
}

// Test 5: Left-deep tree, 5 levels
int test5(void) {
	t_btree *r = btree_create_node(strdup("1"));
	t_btree *curr = r;
	for (int i = 2; i <= 5; i++) {
		curr->left = btree_create_node(strdup("x"));
		curr = curr->left;
	}
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 5) {
		printf("    " RED "[5] Left-deep tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Left-deep tree passed\n" DEFAULT);
	return 0;
}

// Test 6: Right-deep tree, 6 levels
int test6(void) {
	t_btree *r = btree_create_node(strdup("1"));
	t_btree *curr = r;
	for (int i = 2; i <= 6; i++) {
		curr->right = btree_create_node(strdup("x"));
		curr = curr->right;
	}
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 6) {
		printf("    " RED "[6] Right-deep tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Right-deep tree passed\n" DEFAULT);
	return 0;
}

// Test 7: Tree with NULL items but full shape
int test7(void) {
	t_btree *r = btree_create_node(NULL);
	r->left = btree_create_node(NULL);
	r->right = btree_create_node(NULL);
	r->left->left = btree_create_node(NULL);
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 3) {
		printf("    " RED "[7] NULL item nodes failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] NULL item nodes passed\n" DEFAULT);
	return 0;
}

// Test 8: Uneven/mixed shape tree
int test8(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->left->right = btree_create_node(strdup("C"));
	r->left->right->left = btree_create_node(strdup("D"));
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 4) {
		printf("    " RED "[8] Uneven shape tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Uneven shape tree passed\n" DEFAULT);
	return 0;
}

// Test 9: Tree with only one side full (right only)
int test9(void) {
	t_btree *r = btree_create_node(strdup("root"));
	r->right = btree_create_node(strdup("1"));
	r->right->right = btree_create_node(strdup("2"));
	r->right->right->right = btree_create_node(strdup("3"));
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 4) {
		printf("    " RED "[9] Right-only shape failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Right-only shape passed\n" DEFAULT);
	return 0;
}

// Test 10: Large balanced binary tree, depth 6
int test10(void) {
	t_btree *r = btree_create_node(strdup("0"));
	t_btree *nodes[32];
	nodes[0] = r;
	for (int i = 1; i < 32; i++) {
		nodes[i] = btree_create_node(strdup("x"));
	}
	for (int i = 0; i < 32; i++) {
		if (2 * i + 1 < 32)
			nodes[i]->left = nodes[2 * i + 1];
		if (2 * i + 2 < 32)
			nodes[i]->right = nodes[2 * i + 2];
	}
	int result = btree_level_count(r);
	free_tree(r);
	if (result != 6) {
		printf("    " RED "[10] Large tree depth 6 failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Large tree depth 6 passed\n" DEFAULT);
	return 0;
}

// Test 11: Very large balanced binary tree, depth 15 (32767 nodes)
int test11(void) {
	int total_nodes = 32767; // 2^15 - 1
	t_btree **nodes = malloc(sizeof(t_btree *) * total_nodes);
	if (!nodes) {
		printf("    " RED "[11] Allocation failed\n" DEFAULT);
		return -1;
	}
	for (int i = 0; i < total_nodes; i++) {
		nodes[i] = btree_create_node(strdup("x"));
		if (!nodes[i]) {
			printf("    " RED "[11] Node allocation failed\n" DEFAULT);
			for (int j = 0; j < i; j++)
				free(nodes[j]);
			free(nodes);
			return -1;
		}
	}
	for (int i = 0; i < (total_nodes - 1) / 2; i++) {
		nodes[i]->left = nodes[2 * i + 1];
		nodes[i]->right = nodes[2 * i + 2];
	}
	int result = btree_level_count(nodes[0]);
	for (int i = 0; i < total_nodes; i++) {
		free(nodes[i]->item);
		free(nodes[i]);
	}
	free(nodes);
	if (result != 15) {
		printf("    " RED "[11] Large-scale tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [11] Large-scale tree (depth 15) passed\n" DEFAULT);
	return 0;
}

// Test 12: Very deep unbalanced left-heavy tree, depth 25
int test12(void) {
	int depth = 25;
	t_btree *root = btree_create_node(strdup("root"));
	if (!root) {
		printf("    " RED "[12] Root allocation failed\n" DEFAULT);
		return -1;
	}
	t_btree *curr = root;
	for (int i = 1; i < depth; i++) {
		t_btree *new_node = btree_create_node(strdup("x"));
		if (!new_node) {
			printf("    " RED "[12] Node allocation failed at depth %d\n" DEFAULT, i);
			return -1;
		}
		curr->left = new_node;
		curr = new_node;
	}
	int result = btree_level_count(root);

	// Cleanup
	curr = root;
	while (curr) {
		t_btree *next = curr->left;
		free(curr->item);
		free(curr);
		curr = next;
	}
	if (result != depth) {
		printf("    " RED "[12] Unbalanced tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [12] Unbalanced left-heavy tree (depth 25) passed\n" DEFAULT);
	return 0;
}

// Test 13: Very deep unbalanced right-heavy tree, depth 20
int test13(void) {
	int depth = 20;
	t_btree *root = btree_create_node(strdup("root"));
	if (!root) {
		printf("    " RED "[13] Root allocation failed\n" DEFAULT);
		return -1;
	}
	t_btree *curr = root;
	for (int i = 1; i < depth; i++) {
		t_btree *new_node = btree_create_node(strdup("x"));
		if (!new_node) {
			printf("    " RED "[13] Node allocation failed at depth %d\n" DEFAULT, i);
			return -1;
		}
		curr->right = new_node;
		curr = new_node;
	}
	int result = btree_level_count(root);

	// Cleanup
	curr = root;
	while (curr) {
		t_btree *next = curr->right;
		free(curr->item);
		free(curr);
		curr = next;
	}
	if (result != depth) {
		printf("    " RED "[13] Right-heavy tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [13] Right-heavy tree (depth 20) passed\n" DEFAULT);
	return 0;
}

// Test 14: Irregular tree with mixed left/right and gaps (depth 6)
int test14(void) {
	t_btree *root = btree_create_node(strdup("A"));
	root->left = btree_create_node(strdup("B"));
	root->right = btree_create_node(strdup("C"));
	root->left->right = btree_create_node(strdup("D"));
	root->right->left = btree_create_node(strdup("E"));
	root->right->left->right = btree_create_node(strdup("F"));
	root->right->left->right->left = btree_create_node(strdup("G"));
	root->right->left->right->left->right = btree_create_node(strdup("H"));

	int result = btree_level_count(root);

	// Cleanup
	void free_node(void *item) {
		free(item);
	}
	void recursive_free(t_btree *node) {
		if (!node) return;
		recursive_free(node->left);
		recursive_free(node->right);
		free_node(node->item);
		free(node);
	}
	recursive_free(root);

	if (result != 6) {
		printf("    " RED "[14] Irregular tree failed (got %d)\n" DEFAULT, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [14] Irregular branching tree (depth 6) passed\n" DEFAULT);
	return 0;
}
