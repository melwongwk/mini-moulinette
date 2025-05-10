#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_list *ft_create_elem(void *data);
void ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)());
void free_list(t_list *list);
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

void to_uppercase(void *data) {
	char *str = data;
	for (int i = 0; str[i]; ++i)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
}

int cmp_str(void *a, void *b) {
	return strcmp((char *)a, (char *)b);
}

void increment_int(void *data) {
	*(int *)data += 1;
}

int cmp_int(void *a, void *b) {
	return (*(int *)a != *(int *)b);
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

// Test 1: Apply function only to matching element
int test1(void) {
	t_list *list = ft_create_elem(strdup("one"));
	list->next = ft_create_elem(strdup("two"));
	list->next->next = ft_create_elem(strdup("three"));

	ft_list_foreach_if(list, to_uppercase, "two", cmp_str);

	int pass = strcmp(list->data, "one") == 0 &&
	           strcmp(list->next->data, "TWO") == 0 &&
	           strcmp(list->next->next->data, "three") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Match single element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Match single element passed\n" DEFAULT);
	return 0;
}

// Test 2: No elements match
int test2(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));
	list->next->next = ft_create_elem(strdup("cherry"));

	ft_list_foreach_if(list, to_uppercase, "grape", cmp_str);

	int pass = strcmp(list->data, "apple") == 0 &&
	           strcmp(list->next->data, "banana") == 0 &&
	           strcmp(list->next->next->data, "cherry") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] No match apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] No match apply passed\n" DEFAULT);
	return 0;
}

// Test 3: All elements match
int test3(void) {
	t_list *list = ft_create_elem(strdup("same"));
	list->next = ft_create_elem(strdup("same"));
	list->next->next = ft_create_elem(strdup("same"));

	ft_list_foreach_if(list, to_uppercase, "same", cmp_str);

	int pass = strcmp(list->data, "SAME") == 0 &&
	           strcmp(list->next->data, "SAME") == 0 &&
	           strcmp(list->next->next->data, "SAME") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] All match apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] All match apply passed\n" DEFAULT);
	return 0;
}

// Test 4: Empty list
int test4(void) {
	t_list *list = NULL;
	ft_list_foreach_if(list, to_uppercase, "irrelevant", cmp_str);
	printf("  " GREEN CHECKMARK GREY " [4] Empty list handled gracefully\n" DEFAULT);
	return 0;
}

// Test 5: Apply to last element only
int test5(void) {
	t_list *list = ft_create_elem(strdup("start"));
	list->next = ft_create_elem(strdup("middle"));
	list->next->next = ft_create_elem(strdup("end"));

	ft_list_foreach_if(list, to_uppercase, "end", cmp_str);

	int pass = strcmp(list->data, "start") == 0 &&
	           strcmp(list->next->data, "middle") == 0 &&
	           strcmp(list->next->next->data, "END") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[5] Match last element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Match last element passed\n" DEFAULT);
	return 0;
}

int test6(void) {
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	int *c = malloc(sizeof(int));
	*a = 5; *b = 42; *c = 5;

	t_list *list = ft_create_elem(a);
	list->next = ft_create_elem(b);
	list->next->next = ft_create_elem(c);

	int target = 5;
	ft_list_foreach_if(list, increment_int, &target, cmp_int);

	int pass = *a == 6 && *b == 42 && *c == 6;

	free(a); free(b); free(c);
	free(list->next->next); free(list->next); free(list);

	if (!pass) {
		printf("    " RED "[6] Integer match apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Integer match apply passed\n" DEFAULT);
	return 0;
}
