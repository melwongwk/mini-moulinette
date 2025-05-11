#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_merge(t_list **begin_list1, t_list *begin_list2);
void free_list(t_list *list);
int cmp_str(void *a, void *b);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);

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

	return result;
}

// Test 1: Merge two non-empty lists
int test1(void) {
	t_list *a = ft_create_elem(strdup("a1"));
	a->next = ft_create_elem(strdup("a2"));
	t_list *b = ft_create_elem(strdup("b1"));
	b->next = ft_create_elem(strdup("b2"));

	ft_list_merge(&a, b);

	int pass = strcmp(a->next->next->data, "b1") == 0 &&
			   strcmp(a->next->next->next->data, "b2") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[1] Merge two non-empty lists failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Merge two non-empty lists passed\n" DEFAULT);
	return 0;
}

// Test 2: Merge with first list empty
int test2(void) {
	t_list *a = NULL;
	t_list *b = ft_create_elem(strdup("x"));

	ft_list_merge(&a, b);

	int pass = a && strcmp(a->data, "x") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[2] Merge with empty first list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Merge with empty first list passed\n" DEFAULT);
	return 0;
}

// Test 3: Merge with second list empty
int test3(void) {
	t_list *a = ft_create_elem(strdup("a1"));

	ft_list_merge(&a, NULL);

	int pass = a && strcmp(a->data, "a1") == 0 && a->next == NULL;

	free_list(a);
	if (!pass) {
		printf("    " RED "[3] Merge with empty second list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Merge with empty second list passed\n" DEFAULT);
	return 0;
}

// Test 4: Merge two empty lists
int test4(void) {
	t_list *a = NULL;

	ft_list_merge(&a, NULL);

	int pass = a == NULL;

	if (!pass) {
		printf("    " RED "[4] Merge two empty lists failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Merge two empty lists passed\n" DEFAULT);
	return 0;
}

// Test 5: Check merged list maintains order
int test5(void) {
	t_list *a = ft_create_elem(strdup("first"));
	t_list *b = ft_create_elem(strdup("second"));

	ft_list_merge(&a, b);

	int pass = strcmp(a->data, "first") == 0 &&
			   strcmp(a->next->data, "second") == 0 &&
			   a->next->next == NULL;

	free_list(a);
	if (!pass) {
		printf("    " RED "[5] Merge maintains order failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Merge maintains order passed\n" DEFAULT);
	return 0;
}

int test6(void) {
	char *shared = strdup("shared");
	t_list *a = ft_create_elem(shared);
	t_list *b = ft_create_elem(shared);

	ft_list_merge(&a, b);

	int pass = strcmp(a->data, "shared") == 0 &&
			   strcmp(a->next->data, "shared") == 0 &&
			   a->next->next == NULL;

	// Only free the two distinct list elements; shared points to same memory
	free(a->next);
	free(a);
	free(shared);

	if (!pass) {
		printf("    " RED "[6] Shared data pointer merge failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Shared data pointer merge passed\n" DEFAULT);
	return 0;
}
