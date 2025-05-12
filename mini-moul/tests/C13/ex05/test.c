#include "../../../utils/constants.h"
#include "ft_btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_btree *btree_create_node(void *item);
void *btree_search_item(t_btree *root, void *data_ref, int (*cmpf)(void *, void *));
int cmp_str(void *a, void *b);

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

int cmp_str(void *a, void *b) {
	return strcmp((char *)a, (char *)b);
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
	return result;
}

// Test 1: Find root node
int test1(void) {
	t_btree *r = btree_create_node(strdup("A"));
	void *found = btree_search_item(r, "A", cmp_str);
	int pass = (found && strcmp(found, "A") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[1] Search root failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Search root passed\n" DEFAULT);
	return 0;
}

// Test 2: Find left node
int test2(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	void *found = btree_search_item(r, "B", cmp_str);
	int pass = (found && strcmp(found, "B") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[2] Search left child failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Search left child passed\n" DEFAULT);
	return 0;
}

// Test 3: Find right node
int test3(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->right = btree_create_node(strdup("C"));
	void *found = btree_search_item(r, "C", cmp_str);
	int pass = (found && strcmp(found, "C") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[3] Search right child failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Search right child passed\n" DEFAULT);
	return 0;
}

// Test 4: Not found
int test4(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->right = btree_create_node(strdup("C"));
	void *found = btree_search_item(r, "Z", cmp_str);
	int pass = (found == NULL);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[4] Not found failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Not found passed\n" DEFAULT);
	return 0;
}

// Test 5: Deep left
int test5(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->left->left = btree_create_node(strdup("C"));
	void *found = btree_search_item(r, "C", cmp_str);
	int pass = (found && strcmp(found, "C") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[5] Deep left search failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Deep left search passed\n" DEFAULT);
	return 0;
}

// Test 6: Deep right
int test6(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->right = btree_create_node(strdup("B"));
	r->right->right = btree_create_node(strdup("C"));
	void *found = btree_search_item(r, "C", cmp_str);
	int pass = (found && strcmp(found, "C") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[6] Deep right search failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Deep right search passed\n" DEFAULT);
	return 0;
}

// Test 7: NULL root
int test7(void) {
	void *found = btree_search_item(NULL, "A", cmp_str);
	int pass = (found == NULL);
	if (!pass) {
		printf("    " RED "[7] NULL root failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] NULL root passed\n" DEFAULT);
	return 0;
}

// Test 8: NULL item in node
int test8(void) {
	t_btree *r = btree_create_node(NULL);
	r->left = btree_create_node(strdup("B"));
	void *found = btree_search_item(r, "B", cmp_str);
	int pass = (found && strcmp(found, "B") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[8] Search with NULL item failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Search with NULL item passed\n" DEFAULT);
	return 0;
}

// Test 9: Full binary tree
int test9(void) {
	t_btree *r = btree_create_node(strdup("M"));
	r->left = btree_create_node(strdup("L"));
	r->right = btree_create_node(strdup("R"));
	r->left->right = btree_create_node(strdup("N"));
	r->right->left = btree_create_node(strdup("Q"));
	r->right->right = btree_create_node(strdup("S"));
	void *found = btree_search_item(r, "Q", cmp_str);
	int pass = (found && strcmp(found, "Q") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[9] Full binary tree search failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Full binary tree search passed\n" DEFAULT);
	return 0;
}

// Test 10: Search duplicate items (first found)
int test10(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->right = btree_create_node(strdup("B"));
	void *found = btree_search_item(r, "B", cmp_str);
	int pass = (found && strcmp(found, "B") == 0);
	free_tree(r);
	if (!pass) {
		printf("    " RED "[10] Duplicate items search failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Duplicate items search passed\n" DEFAULT);
	return 0;
}
