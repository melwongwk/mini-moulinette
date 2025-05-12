#include "../../../utils/constants.h"
#include "ft_btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_btree *btree_create_node(void *item);
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

// Global collector for test outputs
char result_str[1000];
int result_pos = 0;

void collector(void *item) {
    if (item) {
        char *s = (char *)item;
        int len = strlen(s);
        memcpy(result_str + result_pos, s, len);
        result_pos += len;
    }
}

// Helper
void free_tree(t_btree *node) {
    if (!node) return;
    free(node->item);
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

// Implementation of btree_create_node
t_btree *btree_create_node(void *item) {
    t_btree *node = malloc(sizeof(t_btree));
    if (!node) return NULL;
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void btree_apply_prefix(t_btree *root, void (*applyf)(void *)) {
    if (!root)
        return;
    applyf(root->item);
    btree_apply_prefix(root->left, applyf);
    btree_apply_prefix(root->right, applyf);
}

void btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	btree_apply_suffix(root->left, applyf);
	btree_apply_suffix(root->right, applyf);
	applyf(root->item);
}

int cmp_str(void *a, void *b) {
	return strcmp((char *)a, (char *)b);
}

void reset_collector(void) {
    result_str[0] = '\0';
	result_pos = 0;
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

    return result;
}

// Test 1: Single node
int test1(void) {
    t_btree *root = btree_create_node(strdup("A"));
    result_pos = 0;
    btree_apply_suffix(root, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "A") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[1] Single node traversal failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [1] Single node traversal passed\n" DEFAULT);
    return 0;
}

// Test 2: Two-level tree
int test2(void) {
    t_btree *root = btree_create_node(strdup("A"));
    root->left = btree_create_node(strdup("B"));
    root->right = btree_create_node(strdup("C"));
    result_pos = 0;
    btree_apply_suffix(root, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "BCA") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[2] Two-level suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [2] Two-level suffix passed\n" DEFAULT);
    return 0;
}

// Test 3: Left-heavy tree
int test3(void) {
    t_btree *root = btree_create_node(strdup("A"));
    root->left = btree_create_node(strdup("B"));
    root->left->left = btree_create_node(strdup("C"));
    result_pos = 0;
    btree_apply_suffix(root, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "CBA") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[3] Left-heavy suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [3] Left-heavy suffix passed\n" DEFAULT);
    return 0;
}

// Test 4: Right-heavy tree
int test4(void) {
    t_btree *root = btree_create_node(strdup("A"));
    root->right = btree_create_node(strdup("B"));
    root->right->right = btree_create_node(strdup("C"));
    result_pos = 0;
    btree_apply_suffix(root, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "CBA") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[4] Right-heavy suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [4] Right-heavy suffix passed\n" DEFAULT);
    return 0;
}

// Test 5: Full binary tree (3 levels)
int test5(void) {
    t_btree *r = btree_create_node(strdup("A"));
    r->left = btree_create_node(strdup("B"));
    r->right = btree_create_node(strdup("C"));
    r->left->left = btree_create_node(strdup("D"));
    r->left->right = btree_create_node(strdup("E"));
    r->right->left = btree_create_node(strdup("F"));
    r->right->right = btree_create_node(strdup("G"));
    result_pos = 0;
    btree_apply_suffix(r, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "DEBFGCA") == 0;
    free_tree(r);
    if (!pass) {
        printf("    " RED "[5] Full binary tree suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [5] Full binary tree suffix passed\n" DEFAULT);
    return 0;
}

// Test 6: NULL root
int test6(void) {
    result_pos = 0;
    btree_apply_suffix(NULL, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "") == 0;
    if (!pass) {
        printf("    " RED "[6] NULL root failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [6] NULL root passed\n" DEFAULT);
    return 0;
}

// Test 7: Tree with NULL items
int test7(void) {
    t_btree *root = btree_create_node(NULL);
    root->left = btree_create_node(strdup("X"));
    root->right = btree_create_node(NULL);
    result_pos = 0;
    btree_apply_suffix(root, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "X") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[7] Tree with NULL items failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [7] Tree with NULL items passed\n" DEFAULT);
    return 0;
}

// Test 8: Unbalanced deep left
int test8(void) {
    t_btree *r = btree_create_node(strdup("A"));
    r->left = btree_create_node(strdup("B"));
    r->left->left = btree_create_node(strdup("C"));
    r->left->left->left = btree_create_node(strdup("D"));
    result_pos = 0;
    btree_apply_suffix(r, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "DCBA") == 0;
    free_tree(r);
    if (!pass) {
        printf("    " RED "[8] Unbalanced left tree suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [8] Unbalanced left tree suffix passed\n" DEFAULT);
    return 0;
}

// Test 9: Unbalanced deep right
int test9(void) {
    t_btree *r = btree_create_node(strdup("A"));
    r->right = btree_create_node(strdup("B"));
    r->right->right = btree_create_node(strdup("C"));
    r->right->right->right = btree_create_node(strdup("D"));
    result_pos = 0;
    btree_apply_suffix(r, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "DCBA") == 0;
    free_tree(r);
    if (!pass) {
        printf("    " RED "[9] Unbalanced right tree suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [9] Unbalanced right tree suffix passed\n" DEFAULT);
    return 0;
}

// Test 10: Mixed tree
int test10(void) {
    t_btree *r = btree_create_node(strdup("M"));
    r->left = btree_create_node(strdup("L"));
    r->right = btree_create_node(strdup("R"));
    r->left->right = btree_create_node(strdup("N"));
    r->right->left = btree_create_node(strdup("Q"));
    r->right->right = btree_create_node(strdup("S"));
    result_pos = 0;
    btree_apply_suffix(r, &collector);
    result_str[result_pos] = '\0';
    int pass = strcmp(result_str, "NLQSRM") == 0;
    free_tree(r);
    if (!pass) {
        printf("    " RED "[10] Mixed tree suffix failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [10] Mixed tree suffix passed\n" DEFAULT);
    return 0;
}

// Test 11: Insert into an existing tree
int test11(void) {
    t_btree *root = NULL;
    char *initial[] = {"D", "B", "F"};
    for (int i = 0; i < 3; i++)
        btree_insert_data(&root, strdup(initial[i]), &cmp_str);

    // Insert into the existing tree
    btree_insert_data(&root, strdup("A"), &cmp_str);
    btree_insert_data(&root, strdup("E"), &cmp_str);
    btree_insert_data(&root, strdup("G"), &cmp_str);

    reset_collector();
    btree_apply_prefix(root, &collector);
    int pass = strcmp(result_str, "DBAFEG") == 0;
    free_tree(root);
    if (!pass) {
        printf("    " RED "[11] Insert into existing tree failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [11] Insert into existing tree passed\n" DEFAULT);
    return 0;
}
