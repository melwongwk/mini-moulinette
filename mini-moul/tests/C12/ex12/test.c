#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void free_list(t_list *list);
int cmp_str(void *a, void *b);
void free_str(void *data);
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);
int test7(void);
int test8(void);

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

int cmp_int(void *a, void *b) {
	return (*(int *)a - *(int *)b);
}

void free_str(void *data) {
	free(data);
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

	return result;
}

// Test 1: Remove head
int test1(void) {
	t_list *list = ft_create_elem(strdup("delete"));
	list->next = ft_create_elem(strdup("keep"));

	ft_list_remove_if(&list, "delete", cmp_str, free_str);

	int pass = list && strcmp(list->data, "keep") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Remove head failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Remove head passed\n" DEFAULT);
	return 0;
}

// Test 2: Remove tail
int test2(void) {
	t_list *list = ft_create_elem(strdup("keep"));
	list->next = ft_create_elem(strdup("delete"));

	ft_list_remove_if(&list, "delete", cmp_str, free_str);

	int pass = list && list->next == NULL && strcmp(list->data, "keep") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Remove tail failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Remove tail passed\n" DEFAULT);
	return 0;
}

// Test 3: Remove middle
int test3(void) {
	t_list *list = ft_create_elem(strdup("one"));
	list->next = ft_create_elem(strdup("delete"));
	list->next->next = ft_create_elem(strdup("three"));

	ft_list_remove_if(&list, "delete", cmp_str, free_str);

	int pass = list && list->next && strcmp(list->next->data, "three") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] Remove middle failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Remove middle passed\n" DEFAULT);
	return 0;
}

// Test 4: Remove all
int test4(void) {
	t_list *list = ft_create_elem(strdup("zap"));
	list->next = ft_create_elem(strdup("zap"));
	list->next->next = ft_create_elem(strdup("zap"));

	ft_list_remove_if(&list, "zap", cmp_str, free_str);

	int pass = list == NULL;

	if (!pass) {
		printf("    " RED "[4] Remove all failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Remove all passed\n" DEFAULT);
	return 0;
}

// Test 5: Remove none
int test5(void) {
	t_list *list = ft_create_elem(strdup("a"));
	list->next = ft_create_elem(strdup("b"));

	ft_list_remove_if(&list, "x", cmp_str, free_str);

	int pass = list && list->next && strcmp(list->data, "a") == 0 && strcmp(list->next->data, "b") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[5] Remove none failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Remove none passed\n" DEFAULT);
	return 0;
}

// Test 6: Empty list
int test6(void) {
	t_list *list = NULL;

	ft_list_remove_if(&list, "whatever", cmp_str, free_str);

	int pass = list == NULL;

	if (!pass) {
		printf("    " RED "[6] Empty list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Empty list passed\n" DEFAULT);
	return 0;
}

// Test 7: Remove multiple non-contiguous matches
int test7(void) {
	t_list *list = ft_create_elem(strdup("keep1"));
	list->next = ft_create_elem(strdup("zap"));
	list->next->next = ft_create_elem(strdup("keep2"));
	list->next->next->next = ft_create_elem(strdup("zap"));
	list->next->next->next->next = ft_create_elem(strdup("keep3"));

	ft_list_remove_if(&list, "zap", cmp_str, free_str);

	int pass = list &&
		strcmp(list->data, "keep1") == 0 &&
		list->next && strcmp(list->next->data, "keep2") == 0 &&
		list->next->next && strcmp(list->next->next->data, "keep3") == 0 &&
		list->next->next->next == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[7] Remove multiple non-contiguous failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Remove multiple non-contiguous passed\n" DEFAULT);
	return 0;
}

// Test 8: Remove integer values
int test8(void) {
	int *a = malloc(sizeof(int)); *a = 1;
	int *b = malloc(sizeof(int)); *b = 2;
	int *c = malloc(sizeof(int)); *c = 1;

	t_list *list = ft_create_elem(a);
	list->next = ft_create_elem(b);
	list->next->next = ft_create_elem(c);

	int ref = 1;
	ft_list_remove_if(&list, &ref, cmp_int, free);

	int pass = list && *(int *)list->data == 2 && list->next == NULL;

	free(list->data);
	free(list);
	if (!pass) {
		printf("    " RED "[8] Remove integer values failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Remove integer values passed\n" DEFAULT);
	return 0;
}
