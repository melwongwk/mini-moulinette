#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
t_list *ft_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
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

// Test 1: Match first element
int test1(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));

	t_list *found = ft_list_find(list, "apple", cmp_str);

	int pass = found && strcmp(found->data, "apple") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Match first element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Match first element passed\n" DEFAULT);
	return 0;
}

// Test 2: Match last element
int test2(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));
	list->next->next = ft_create_elem(strdup("cherry"));

	t_list *found = ft_list_find(list, "cherry", cmp_str);

	int pass = found && strcmp(found->data, "cherry") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Match last element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Match last element passed\n" DEFAULT);
	return 0;
}

// Test 3: No match
int test3(void) {
	t_list *list = ft_create_elem(strdup("one"));
	list->next = ft_create_elem(strdup("two"));

	t_list *found = ft_list_find(list, "three", cmp_str);

	int pass = found == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] No match failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] No match passed\n" DEFAULT);
	return 0;
}

// Test 4: Empty list
int test4(void) {
	t_list *list = NULL;

	t_list *found = ft_list_find(list, "any", cmp_str);

	int pass = found == NULL;

	if (!pass) {
		printf("    " RED "[4] Empty list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Empty list passed\n" DEFAULT);
	return 0;
}

// Test 5: All elements match — should return first
int test5(void) {
	char *shared = strdup("match");
	t_list *list = ft_create_elem(shared);
	list->next = ft_create_elem(shared);
	list->next->next = ft_create_elem(shared);

	t_list *found = ft_list_find(list, "match", cmp_str);

	int pass = found == list;

	free(list->next->next);
	free(list->next);
	free(list);
	free(shared);

	if (!pass) {
		printf("    " RED "[5] All match first return failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] All match first return passed\n" DEFAULT);
	return 0;
}

// Test 6: Match middle element
int test6(void) {
	t_list *list = ft_create_elem(strdup("one"));
	list->next = ft_create_elem(strdup("target"));
	list->next->next = ft_create_elem(strdup("three"));

	t_list *found = ft_list_find(list, "target", cmp_str);

	int pass = found && strcmp(found->data, "target") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[6] Match middle element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Match middle element passed\n" DEFAULT);
	return 0;
}
