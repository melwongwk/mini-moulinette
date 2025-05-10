#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_reverse(t_list **begin_list);
void free_list(t_list *list);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);
int test7(void);

// Helpers
t_list *ft_create_elem(void *data) {
	t_list *elem = malloc(sizeof(t_list));
	if (!elem) return NULL;
	elem->data = data;
	elem->next = NULL;
	return elem;
}

void free_list(t_list *list) {
	t_list *tmp;
	while (list) {
		tmp = list->next;
		free(list->data);
		free(list);
		list = tmp;
	}
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

	return result;
}

// Test 1: Reverse a list of 3 elements
int test1(void) {
	t_list *list = ft_create_elem(strdup("one"));
	list->next = ft_create_elem(strdup("two"));
	list->next->next = ft_create_elem(strdup("three"));

	ft_list_reverse(&list);

	int pass = strcmp(list->data, "three") == 0 &&
	           strcmp(list->next->data, "two") == 0 &&
	           strcmp(list->next->next->data, "one") == 0 &&
	           list->next->next->next == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Reverse 3-element list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Reverse 3-element list passed\n" DEFAULT);
	return 0;
}

// Test 2: Reverse a single-element list
int test2(void) {
	t_list *list = ft_create_elem(strdup("solo"));
	ft_list_reverse(&list);

	int pass = list && strcmp(list->data, "solo") == 0 && list->next == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Single-element list reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Single-element list reverse passed\n" DEFAULT);
	return 0;
}

// Test 3: Reverse an empty list
int test3(void) {
	t_list *list = NULL;
	ft_list_reverse(&list);

	if (list != NULL) {
		printf("    " RED "[3] Empty list reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Empty list reverse passed\n" DEFAULT);
	return 0;
}

// Test 4: Boundary case - two elements
int test4(void) {
	t_list *list = ft_create_elem(strdup("first"));
	list->next = ft_create_elem(strdup("second"));

	ft_list_reverse(&list);

	int pass = strcmp(list->data, "second") == 0 &&
	           strcmp(list->next->data, "first") == 0 &&
	           list->next->next == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[4] Two-element list reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Two-element list reverse passed\n" DEFAULT);
	return 0;
}

// Test 5: Reverse a long list (20 elements)
int test5(void) {
	t_list *head = NULL, *current = NULL;
	char buffer[10];

	for (int i = 0; i < 20; i++) {
		snprintf(buffer, sizeof(buffer), "%d", i);
		t_list *new_elem = ft_create_elem(strdup(buffer));
		if (!head)
			head = new_elem;
		else
			current->next = new_elem;
		current = new_elem;
	}

	ft_list_reverse(&head);

	// Expect values from 19 down to 0
	current = head;
	int i = 19, pass = 1;
	while (current && i >= 0) {
		snprintf(buffer, sizeof(buffer), "%d", i--);
		if (strcmp(current->data, buffer) != 0) {
			pass = 0;
			break;
		}
		current = current->next;
	}
	pass = pass && current == NULL;

	free_list(head);
	if (!pass) {
		printf("    " RED "[5] Long list reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Long list reverse passed\n" DEFAULT);
	return 0;
}

// Test 6: Identical values in the list
int test6(void) {
	t_list *a = ft_create_elem(strdup("x"));
	t_list *b = ft_create_elem(strdup("x"));
	t_list *c = ft_create_elem(strdup("x"));
	a->next = b; b->next = c;

	ft_list_reverse(&a);

	int pass = a && a->next && a->next->next && a->next->next->next == NULL;
	free_list(a);
	if (!pass) {
		printf("    " RED "[6] Identical values test failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Identical values reverse passed\n" DEFAULT);
	return 0;
}

// Test 7: Dynamically allocated strings in list
int test7(void) {
	t_list *a = ft_create_elem(strdup("A"));
	t_list *b = ft_create_elem(strdup("B"));
	t_list *c = ft_create_elem(strdup("C"));
	a->next = b; b->next = c;

	ft_list_reverse(&a);

	int pass = strcmp(a->data, "C") == 0 &&
	           strcmp(a->next->data, "B") == 0 &&
	           strcmp(a->next->next->data, "A") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[7] Dynamic strings reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Dynamic strings reverse passed\n" DEFAULT);
	return 0;
}
