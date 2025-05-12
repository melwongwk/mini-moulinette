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

// Helper
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
    return result;
}

// Test 1: Create with string
int test1(void) {
    char *str = strdup("hello");
    t_btree *node = btree_create_node(str);
    int pass = node && node->item == str && node->left == NULL && node->right == NULL;
    free_tree(node);
    if (!pass) {
        printf("    " RED "[1] String node creation failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [1] String node creation passed\n" DEFAULT);
    return 0;
}

// Test 2: Create with integer
int test2(void) {
    int *val = malloc(sizeof(int));
    *val = 42;
    t_btree *node = btree_create_node(val);
    int pass = node && *(int *)(node->item) == 42 && !node->left && !node->right;
    free_tree(node);
    if (!pass) {
        printf("    " RED "[2] Integer node creation failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [2] Integer node creation passed\n" DEFAULT);
    return 0;
}

// Test 3: NULL item
int test3(void) {
    t_btree *node = btree_create_node(NULL);
    int pass = node && node->item == NULL && !node->left && !node->right;
    free(node);
    if (!pass) {
        printf("    " RED "[3] NULL item failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [3] NULL item passed\n" DEFAULT);
    return 0;
}

// Test 4: Verify left and right are NULL
int test4(void) {
    t_btree *node = btree_create_node(strdup("x"));
    int pass = node && node->left == NULL && node->right == NULL;
    free_tree(node);
    if (!pass) {
        printf("    " RED "[4] Left/right NULL check failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [4] Left/right NULL check passed\n" DEFAULT);
    return 0;
}

// Test 5: Create multiple nodes
int test5(void) {
    t_btree *n1 = btree_create_node(strdup("n1"));
    t_btree *n2 = btree_create_node(strdup("n2"));
    t_btree *n3 = btree_create_node(strdup("n3"));

    int pass = n1 && n2 && n3 && strcmp(n1->item, "n1") == 0 &&
               strcmp(n2->item, "n2") == 0 && strcmp(n3->item, "n3") == 0;

    free_tree(n1);
    free_tree(n2);
    free_tree(n3);

    if (!pass) {
        printf("    " RED "[5] Multiple nodes creation failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [5] Multiple nodes creation passed\n" DEFAULT);
    return 0;
}

// Test 6: Large string item
int test6(void) {
    char *long_str = malloc(1000);
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    t_btree *node = btree_create_node(long_str);
    int pass = node && node->item && ((char *)node->item)[998] == 'A';
    free_tree(node);
    if (!pass) {
        printf("    " RED "[6] Long string node failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [6] Long string node passed\n" DEFAULT);
    return 0;
}

// Test 7: Free item and ensure node still allocates
int test7(void) {
    char *s = strdup("free_me");
    t_btree *node = btree_create_node(s);
    int pass = node != NULL;
    free_tree(node);
    if (!pass) {
        printf("    " RED "[7] Free item after node creation failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [7] Free item after node creation passed\n" DEFAULT);
    return 0;
}

// Test 8: Check address consistency
int test8(void) {
    int *x = malloc(sizeof(int));
    *x = 123;
    t_btree *node = btree_create_node(x);
    int pass = node && node->item == x;
    free_tree(node);
    if (!pass) {
        printf("    " RED "[8] Pointer consistency failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [8] Pointer consistency passed\n" DEFAULT);
    return 0;
}

// Test 9: Check structure size
int test9(void) {
    int expected = sizeof(t_btree);
    int actual = sizeof(struct s_btree);
    if (expected != actual) {
        printf("    " RED "[9] Struct size mismatch\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [9] Struct size check passed\n" DEFAULT);
    return 0;
}

// Test 10: Deep memory allocation check (no segfault)
int test10(void) {
    for (int i = 0; i < 1000; i++) {
        int *n = malloc(sizeof(int));
        *n = i;
        t_btree *node = btree_create_node(n);
        if (!node || *(int *)node->item != i) {
            printf("    " RED "[10] Memory stress test failed at i=%d\n" DEFAULT, i);
            free_tree(node);
            return -1;
        }
        free_tree(node);
    }
    printf("  " GREEN CHECKMARK GREY " [10] Memory stress test passed\n" DEFAULT);
    return 0;
}
