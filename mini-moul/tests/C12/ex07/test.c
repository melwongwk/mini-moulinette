#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
t_list *ft_list_at(t_list *begin_list, unsigned int nbr);
void free_list(t_list *list);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);
int test7(void);  // Single element list test
int test8(void);  // Boundary test (last valid index)

// Create an element
t_list *ft_create_elem(void *data) {
    t_list *elem = malloc(sizeof(t_list));
    if (!elem)
        return NULL;
    elem->data = data;
    elem->next = NULL;
    return elem;
}

// Free a full list
void free_list(t_list *list) {
    t_list *tmp;
    while (list) {
        tmp = list->next;
        free(list->data);
        free(list);
        list = tmp;
    }
}

int main(void) {
    int result = 0;

    if (test1() != 0) result = -1;
    if (test2() != 0) result = -1;
    if (test3() != 0) result = -1;
    if (test4() != 0) result = -1;
    if (test5() != 0) result = -1;
    if (test6() != 0) result = -1;
    if (test7() != 0) result = -1;  // Added single element test
    if (test8() != 0) result = -1;  // Added boundary test

    return result;
}

// Test 1: Basic retrieval
int test1(void) {
    t_list *list = ft_create_elem(strdup("First"));
    t_list *second = ft_create_elem(strdup("Second"));
    t_list *third = ft_create_elem(strdup("Third"));
    list->next = second;
    second->next = third;

    t_list *result = ft_list_at(list, 1);
    int pass = result && strcmp(result->data, "Second") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[1] Retrieve index 1 failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [1] Retrieve index 1 passed\n" DEFAULT);
    return 0;
}

// Test 2: Index 0 (first element)
int test2(void) {
    t_list *list = ft_create_elem(strdup("Alpha"));
    t_list *result = ft_list_at(list, 0);
    int pass = result && strcmp(result->data, "Alpha") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[2] Retrieve index 0 failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [2] Retrieve index 0 passed\n" DEFAULT);
    return 0;
}

// Test 3: Last valid index
int test3(void) {
    t_list *list = ft_create_elem(strdup("One"));
    list->next = ft_create_elem(strdup("Two"));
    list->next->next = ft_create_elem(strdup("Three"));

    t_list *result = ft_list_at(list, 2);
    int pass = result && strcmp(result->data, "Three") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[3] Retrieve last index failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [3] Retrieve last index passed\n" DEFAULT);
    return 0;
}

// Test 4: Index out of bounds
int test4(void) {
    t_list *list = ft_create_elem(strdup("Only"));
    t_list *result = ft_list_at(list, 3);
    int pass = result == NULL;

    free_list(list);
    if (!pass) {
        printf("    " RED "[4] Out of bounds index test failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [4] Out of bounds index test passed\n" DEFAULT);
    return 0;
}

// Test 5: NULL list
int test5(void) {
    t_list *list = NULL;
    t_list *result = ft_list_at(list, 0);
    if (result != NULL) {
        printf("    " RED "[5] NULL list test failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [5] NULL list test passed\n" DEFAULT);
    return 0;
}

// Test 6: Long list retrieval
int test6(void) {
    t_list *head = ft_create_elem(strdup("0"));
    t_list *current = head;
    char buffer[10];

    // Populate the list with 20 elements, numbered "0" through "19"
    for (int i = 1; i < 20; ++i) {
        snprintf(buffer, sizeof(buffer), "%d", i);
        current->next = ft_create_elem(strdup(buffer));
        current = current->next;
    }

    // Check if the 19th element exists and has the correct data
    t_list *result = ft_list_at(head, 19);  // Index 19 is the last element
    int pass = result && strcmp(result->data, "19") == 0;

    // Check if the 18th element exists and has the correct data
    result = ft_list_at(head, 18);
    pass = pass && result && strcmp(result->data, "18") == 0;

    // Free the list
    free_list(head);

    if (!pass) {
        printf("    " RED "[6] Long list access test failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [6] Long list access test passed\n" DEFAULT);
    return 0;
}


// Test 7: Single element list
int test7(void) {
    t_list *list = ft_create_elem(strdup("Single"));
    t_list *result = ft_list_at(list, 0);
    int pass = result && strcmp(result->data, "Single") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[7] Single element list failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [7] Single element list passed\n" DEFAULT);
    return 0;
}

// Test 8: Boundary test (last valid index)
int test8(void) {
    t_list *list = ft_create_elem(strdup("First"));
    t_list *second = ft_create_elem(strdup("Second"));
    list->next = second;

    t_list *result = ft_list_at(list, 1);
    int pass = result && strcmp(result->data, "Second") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[8] Boundary test (last valid index) failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [8] Boundary test (last valid index) passed\n" DEFAULT);
    return 0;
}
