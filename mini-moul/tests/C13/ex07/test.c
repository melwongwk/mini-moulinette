#include "../../../utils/constants.h"
#include "ft_btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_btree *btree_create_node(void *item);
void btree_apply_by_level(t_btree *root, void (*applyf)(void *item, int current_level, int is_first_elem));
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
int test15(void);
int test16(void);
int test17(void);
int test18(void);
int test19(void);
int test20(void);

// Globals
char buffer[1024];
int buf_index;

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

void reset_buffer(void) {
	buf_index = 0;
	buffer[0] = '\0';
}

void collect(void *item, int current_level, int is_first_elem) {
	if (is_first_elem)
		buf_index += sprintf(buffer + buf_index, "|");
	buf_index += sprintf(buffer + buf_index, "%s(%d)", (char *)item, current_level);
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
	if (test15() != 0) result = -1;
	if (test16() != 0) result = -1;
	if (test17() != 0) result = -1;
	if (test18() != 0) result = -1;
	if (test19() != 0) result = -1;
	if (test20() != 0) result = -1;
	return result;
}

// Test 1: NULL tree
int test1(void) {
	reset_buffer();
	btree_apply_by_level(NULL, collect);
	if (buffer[0] != '\0') {
		printf("    " RED "[1] NULL root failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] NULL root passed\n" DEFAULT);
	return 0;
}

// Test 2: One node
int test2(void) {
	t_btree *r = btree_create_node(strdup("A"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)") != 0) {
		printf("    " RED "[2] Single node failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Single node passed\n" DEFAULT);
	return 0;
}

// Test 3: Two nodes (root and left)
int test3(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)") != 0) {
		printf("    " RED "[3] Left child failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Left child passed\n" DEFAULT);
	return 0;
}

// Test 4: Root + left + right
int test4(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->right = btree_create_node(strdup("C"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)C(1)") != 0) {
		printf("    " RED "[4] Two children failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Two children passed\n" DEFAULT);
	return 0;
}

// Test 5: Three levels full
int test5(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->right = btree_create_node(strdup("C"));
	r->left->left = btree_create_node(strdup("D"));
	r->left->right = btree_create_node(strdup("E"));
	r->right->left = btree_create_node(strdup("F"));
	r->right->right = btree_create_node(strdup("G"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)C(1)|D(2)E(2)F(2)G(2)") != 0) {
		printf("    " RED "[5] Full tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Full tree passed\n" DEFAULT);
	return 0;
}

// Test 6: Left deep tree
int test6(void) {
	t_btree *r = btree_create_node(strdup("A"));
	t_btree *curr = r;
	for (char c = 'B'; c <= 'F'; c++) {
		curr->left = btree_create_node(strdup((char[]){c, '\0'}));
		curr = curr->left;
	}
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)|C(2)|D(3)|E(4)|F(5)") != 0) {
		printf("    " RED "[6] Left deep failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Left deep passed\n" DEFAULT);
	return 0;
}

// Test 7: Right deep tree
int test7(void) {
	t_btree *r = btree_create_node(strdup("1"));
	t_btree *curr = r;
	for (int i = 2; i <= 6; i++) {
		char s[2] = {(char)(i + '0'), '\0'};
		curr->right = btree_create_node(strdup(s));
		curr = curr->right;
	}
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|1(0)|2(1)|3(2)|4(3)|5(4)|6(5)") != 0) {
		printf("    " RED "[7] Right deep failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Right deep passed\n" DEFAULT);
	return 0;
}

// Test 8: Mixed shape
int test8(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->left->right = btree_create_node(strdup("C"));
	r->left->right->left = btree_create_node(strdup("D"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)|C(2)|D(3)") != 0) {
		printf("    " RED "[8] Mixed tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Mixed tree passed\n" DEFAULT);
	return 0;
}

// Test 9: All NULL items
int test9(void) {
	t_btree *r = btree_create_node(NULL);
	r->left = btree_create_node(NULL);
	r->right = btree_create_node(NULL);
	r->left->left = btree_create_node(NULL);
	reset_buffer();
	void null_collector(void *item, int level, int first) {
		if (first) buf_index += sprintf(buffer + buf_index, "|");
		buf_index += sprintf(buffer + buf_index, "X(%d)", level);
	}
	btree_apply_by_level(r, null_collector);
	free_tree(r);
	if (strcmp(buffer, "|X(0)|X(1)X(1)|X(2)") != 0) {
		printf("    " RED "[9] NULL items failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] NULL items passed\n" DEFAULT);
	return 0;
}

// Test 10: Tree with duplicate values
int test10(void) {
	t_btree *r = btree_create_node(strdup("X"));
	r->left = btree_create_node(strdup("X"));
	r->right = btree_create_node(strdup("X"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|X(0)|X(1)X(1)") != 0) {
		printf("    " RED "[10] Duplicates failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Duplicates passed\n" DEFAULT);
	return 0;
}

// Test 11: Callback modifying external state
int test11(void) {
	int sum = 0;
	t_btree *r = btree_create_node(strdup("1"));
	r->left = btree_create_node(strdup("2"));
	r->right = btree_create_node(strdup("3"));
	void sum_ints(void *item, int level, int is_first) {
		sum += atoi(item);
	}
	btree_apply_by_level(r, sum_ints);
	free_tree(r);
	if (sum != 6) {
		printf("    " RED "[11] Sum callback failed (got %d)\n" DEFAULT, sum);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [11] Sum callback passed\n" DEFAULT);
	return 0;
}

// Test 12: Sparse tree
int test12(void) {
	t_btree *r = btree_create_node(strdup("A"));
	r->left = btree_create_node(strdup("B"));
	r->left->right = btree_create_node(strdup("C"));
	r->left->right->right = btree_create_node(strdup("D"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|A(0)|B(1)|C(2)|D(3)") != 0) {
		printf("    " RED "[12] Sparse tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [12] Sparse tree passed\n" DEFAULT);
	return 0;
}

// Test 13: Zig-zag pattern
int test13(void) {
	t_btree *r = btree_create_node(strdup("1"));
	r->right = btree_create_node(strdup("2"));
	r->right->left = btree_create_node(strdup("3"));
	r->right->left->right = btree_create_node(strdup("4"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|1(0)|2(1)|3(2)|4(3)") != 0) {
		printf("    " RED "[13] Zig-zag tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [13] Zig-zag tree passed\n" DEFAULT);
	return 0;
}

// Test 14: Wide level tree
int test14(void) {
	t_btree *r = btree_create_node(strdup("R"));
	const int WIDTH = 10;
	for (int i = 0; i < WIDTH; ++i) {
		char label[3] = {(char)('A' + i), '\0'};
		t_btree *child = btree_create_node(strdup(label));
		if (i == 0)
			r->left = child;
		else {
			t_btree *curr = r->left;
			while (curr->right)
				curr = curr->right;
			curr->right = child;
		}
	}
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|R(0)|A(1)|B(2)|C(3)|D(4)|E(5)|F(6)|G(7)|H(8)|I(9)|J(10)") != 0) {
		printf("    " RED "[14] Wide level failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [14] Wide level passed\n" DEFAULT);
	return 0;
}

// Test 15: Very wide second level
int test15(void) {
	t_btree *r = btree_create_node(strdup("R"));
	r->left = btree_create_node(strdup("A"));
	r->right = btree_create_node(strdup("B"));
	r->left->left = btree_create_node(strdup("C"));
	r->left->right = btree_create_node(strdup("D"));
	r->right->left = btree_create_node(strdup("E"));
	r->right->right = btree_create_node(strdup("F"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|R(0)|A(1)B(1)|C(2)D(2)E(2)F(2)") != 0) {
		printf("    " RED "[15] Wide second level failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [15] Wide second level passed\n" DEFAULT);
	return 0;
}

// Test 16: One-sided sparse tree (zig-zag)
int test16(void) {
	t_btree *r = btree_create_node(strdup("1"));
	r->right = btree_create_node(strdup("2"));
	r->right->left = btree_create_node(strdup("3"));
	r->right->left->right = btree_create_node(strdup("4"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|1(0)|2(1)|3(2)|4(3)") != 0) {
		printf("    " RED "[16] Zig-zag tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [16] Zig-zag tree passed\n" DEFAULT);
	return 0;
}

// Test 17: Uneven height branches
int test17(void) {
	t_btree *r = btree_create_node(strdup("R"));
	r->left = btree_create_node(strdup("L1"));
	r->right = btree_create_node(strdup("R1"));
	r->left->left = btree_create_node(strdup("L2"));
	r->left->left->left = btree_create_node(strdup("L3"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|R(0)|L1(1)R1(1)|L2(2)|L3(3)") != 0) {
		printf("    " RED "[17] Uneven height failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [17] Uneven height passed\n" DEFAULT);
	return 0;
}

// Test 18: Wide shallow tree
int test18(void) {
	t_btree *r = btree_create_node(strdup("Root"));
	for (char c = 'A'; c <= 'H'; c++) {
		char *val = malloc(2); val[0] = c; val[1] = '\0';
		if (c % 2 == 0)
			r->left = btree_create_node(val);
		else
			r->right = btree_create_node(val);
	}
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	// Since left and right are overwritten, only last values remain
	if (strcmp(buffer, "|Root(0)|H(1)G(1)") != 0) {
		printf("    " RED "[18] Wide shallow tree failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [18] Wide shallow tree passed\n" DEFAULT);
	return 0;
}

// Test 19: Tree with scattered NULL children
int test19(void) {
	t_btree *r = btree_create_node(strdup("Root"));
	r->left = btree_create_node(strdup("L1"));
	r->right = btree_create_node(strdup("R1"));
	r->left->right = btree_create_node(strdup("L2"));
	r->right->left = btree_create_node(strdup("R2"));
	r->left->right->left = btree_create_node(strdup("L3"));
	r->right->left->right = btree_create_node(strdup("R3"));
	reset_buffer();
	btree_apply_by_level(r, collect);
	free_tree(r);
	if (strcmp(buffer, "|Root(0)|L1(1)R1(1)|L2(2)R2(2)|L3(3)R3(3)") != 0) {
		printf("    " RED "[19] NULL scattered failed (got \"%s\")\n" DEFAULT, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [19] NULL scattered passed\n" DEFAULT);
	return 0;
}

// Test 20: Large left-skewed tree (stress test)
int test20(void) {
	t_btree *root = btree_create_node(strdup("N0"));
	t_btree *curr = root;
	char label[16];
	for (int i = 1; i < 101; i++) {
		snprintf(label, sizeof(label), "N%d", i);
		curr->left = btree_create_node(strdup(label));
		curr = curr->left;
	}
	reset_buffer();
	btree_apply_by_level(root, collect);
	free_tree(root);
	// Verify only first and last label to avoid massive output
	if (strncmp(buffer, "|N0(0)|N1(1)", 11) != 0 || strstr(buffer, "N100(100)") == NULL) {
		printf("    " RED "[20] Large tree failed (partial: \"%.*s...\")\n" DEFAULT, 40, buffer);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [20] Large tree passed\n" DEFAULT);
	return 0;
}
