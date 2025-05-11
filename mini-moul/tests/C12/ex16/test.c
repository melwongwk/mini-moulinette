#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_list *ft_create_elem(void *data);
void ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)());
void free_list(t_list *list);
int cmp_str(void *a, void *b);
int cmp_int(void *a, void *b);
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

int cmp_int(void *a, void *b) {
	return (*(int *)a - *(int *)b);
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

// Test 1: Insert into empty list
int test1(void) {
	t_list *list = NULL;

	ft_sorted_list_insert(&list, strdup("apple"), cmp_str);

	int pass = list && strcmp(list->data, "apple") == 0 && list->next == NULL;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Insert into empty failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Insert into empty passed\n" DEFAULT);
	return 0;
}

// Test 2: Insert at head
int test2(void) {
	t_list *list = ft_create_elem(strdup("banana"));
	list->next = ft_create_elem(strdup("cherry"));

	ft_sorted_list_insert(&list, strdup("apple"), cmp_str);

	int pass = strcmp(list->data, "apple") == 0 &&
	           strcmp(list->next->data, "banana") == 0 &&
	           strcmp(list->next->next->data, "cherry") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Insert at head failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Insert at head passed\n" DEFAULT);
	return 0;
}

// Test 3: Insert in middle
int test3(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("cherry"));

	ft_sorted_list_insert(&list, strdup("banana"), cmp_str);

	int pass = strcmp(list->data, "apple") == 0 &&
	           strcmp(list->next->data, "banana") == 0 &&
	           strcmp(list->next->next->data, "cherry") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] Insert in middle failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Insert in middle passed\n" DEFAULT);
	return 0;
}

// Test 4: Insert at end
int test4(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));

	ft_sorted_list_insert(&list, strdup("zebra"), cmp_str);

	int pass = strcmp(list->next->next->data, "zebra") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[4] Insert at end failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Insert at end passed\n" DEFAULT);
	return 0;
}

// Test 5: Insert duplicate
int test5(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));
	list->next->next = ft_create_elem(strdup("cherry"));

	ft_sorted_list_insert(&list, strdup("banana"), cmp_str);

	int count = 0;
	t_list *cur = list;
	while (cur) {
		if (strcmp(cur->data, "banana") == 0)
			count++;
		cur = cur->next;
	}

	int pass = count == 2;

	free_list(list);
	if (!pass) {
		printf("    " RED "[5] Insert duplicate failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Insert duplicate passed\n" DEFAULT);
	return 0;
}

// Test 6: Insert numeric values
int test6(void) {
	int *a = malloc(sizeof(int)); *a = 1;
	int *b = malloc(sizeof(int)); *b = 3;
	int *c = malloc(sizeof(int)); *c = 4;
	int *insert = malloc(sizeof(int)); *insert = 2;

	t_list *list = ft_create_elem(a);
	list->next = ft_create_elem(b);
	list->next->next = ft_create_elem(c);

	ft_sorted_list_insert(&list, insert, cmp_int);

	int pass = *(int *)list->data == 1 &&
	           *(int *)list->next->data == 2 &&
	           *(int *)list->next->next->data == 3 &&
	           *(int *)list->next->next->next->data == 4;

	free_list(list);
	if (!pass) {
		printf("    " RED "[6] Insert numeric failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Insert numeric passed\n" DEFAULT);
	return 0;
}

// Test 7: All elements equal
int test7(void) {
	t_list *list = ft_create_elem(strdup("same"));
	list->next = ft_create_elem(strdup("same"));

	ft_sorted_list_insert(&list, strdup("same"), cmp_str);

	int count = 0;
	t_list *cur = list;
	while (cur) {
		if (strcmp(cur->data, "same") == 0)
			count++;
		cur = cur->next;
	}

	int pass = count == 3;

	free_list(list);
	if (!pass) {
		printf("    " RED "[7] All equal elements failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] All equal elements passed\n" DEFAULT);
	return 0;
}

// Test 8: Insert long string
int test8(void) {
	t_list *list = ft_create_elem(strdup("abc"));
	list->next = ft_create_elem(strdup("def"));

	char *long_str = strdup("zzzzzzzzzz");
	ft_sorted_list_insert(&list, long_str, cmp_str);

	t_list *cur = list;
	while (cur->next) cur = cur->next;

	int pass = strcmp(cur->data, long_str) == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[8] Insert long string failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Insert long string passed\n" DEFAULT);
	return 0;
}

// Test 9: Insert numeric string
int test9(void) {
	t_list *list = ft_create_elem(strdup("1"));
	list->next = ft_create_elem(strdup("3"));

	ft_sorted_list_insert(&list, strdup("2"), cmp_str);

	int pass = strcmp(list->next->data, "2") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[9] Insert numeric string failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Insert numeric string passed\n" DEFAULT);
	return 0;
}

int test10(void) {
	t_list *list = NULL;

	// Defensive comparison: cmp_str must guard against NULL
	int safe_cmp(void *a, void *b) {
		if (!a && !b) return 0;
		if (!a) return -1;
		if (!b) return 1;
		return strcmp((char *)a, (char *)b);
	}

	// Insert nodes with some NULL data
	ft_sorted_list_insert(&list, strdup("banana"), safe_cmp);
	ft_sorted_list_insert(&list, NULL, safe_cmp);          // NULL should go first
	ft_sorted_list_insert(&list, strdup("apple"), safe_cmp);

	// Validate order: NULL -> "apple" -> "banana"
	int pass = list && list->data == NULL &&
	           list->next && strcmp(list->next->data, "apple") == 0 &&
	           list->next->next && strcmp(list->next->next->data, "banana") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[10] NULL-safe insert failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] NULL-safe insert passed\n" DEFAULT);
	return 0;
}

