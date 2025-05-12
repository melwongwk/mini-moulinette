#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_list *ft_create_elem(void *data);
void ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2, int (*cmp)());
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

void append_node(t_list **head, char *str) {
	t_list *new = ft_create_elem(strdup(str));
	if (!*head) {
		*head = new;
		return;
	}
	t_list *cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
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

// Test 1: Merge into empty list
int test1(void) {
	t_list *a = NULL;
	t_list *b = ft_create_elem(strdup("apple"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int pass = a && strcmp(a->data, "apple") == 0 && a->next == NULL;

	free_list(a);
	if (!pass) {
		printf("    " RED "[1] Merge into empty failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Merge into empty passed\n" DEFAULT);
	return 0;
}

// Test 2: Merge empty into list
int test2(void) {
	t_list *a = ft_create_elem(strdup("apple"));
	t_list *b = NULL;

	ft_sorted_list_merge(&a, b, cmp_str);

	int pass = a && strcmp(a->data, "apple") == 0 && a->next == NULL;

	free_list(a);
	if (!pass) {
		printf("    " RED "[2] Merge empty into list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Merge empty into list passed\n" DEFAULT);
	return 0;
}

// Test 3: Merge into head
int test3(void) {
	t_list *a = ft_create_elem(strdup("banana"));
	t_list *b = ft_create_elem(strdup("apple"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int pass = strcmp(a->data, "apple") == 0 &&
	           strcmp(a->next->data, "banana") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[3] Merge into head failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Merge into head passed\n" DEFAULT);
	return 0;
}

// Test 4: Merge into tail
int test4(void) {
	t_list *a = ft_create_elem(strdup("apple"));
	t_list *b = ft_create_elem(strdup("banana"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int pass = strcmp(a->data, "apple") == 0 &&
	           strcmp(a->next->data, "banana") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[4] Merge into tail failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Merge into tail passed\n" DEFAULT);
	return 0;
}

// Test 5: Merge with middle insert
int test5(void) {
	t_list *a = ft_create_elem(strdup("apple"));
	a->next = ft_create_elem(strdup("cherry"));
	t_list *b = ft_create_elem(strdup("banana"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int pass = strcmp(a->data, "apple") == 0 &&
	           strcmp(a->next->data, "banana") == 0 &&
	           strcmp(a->next->next->data, "cherry") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[5] Merge with middle insert failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Merge with middle insert passed\n" DEFAULT);
	return 0;
}

// Test 6: Merge two sorted numeric lists
int test6(void) {
	int *a1 = malloc(sizeof(int)); *a1 = 1;
	int *a2 = malloc(sizeof(int)); *a2 = 3;
	t_list *a = ft_create_elem(a1);
	a->next = ft_create_elem(a2);

	int *b1 = malloc(sizeof(int)); *b1 = 2;
	int *b2 = malloc(sizeof(int)); *b2 = 4;
	t_list *b = ft_create_elem(b1);
	b->next = ft_create_elem(b2);

	ft_sorted_list_merge(&a, b, cmp_int);

	int pass = *(int *)a->data == 1 &&
	           *(int *)a->next->data == 2 &&
	           *(int *)a->next->next->data == 3 &&
	           *(int *)a->next->next->next->data == 4;

	free_list(a);
	if (!pass) {
		printf("    " RED "[6] Merge sorted numeric lists failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Merge sorted numeric lists passed\n" DEFAULT);
	return 0;
}

// Test 7: Merge lists with duplicates
int test7(void) {
	t_list *a = ft_create_elem(strdup("apple"));
	a->next = ft_create_elem(strdup("banana"));

	t_list *b = ft_create_elem(strdup("banana"));
	b->next = ft_create_elem(strdup("cherry"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int count = 0;
	t_list *cur = a;
	while (cur) {
		if (strcmp(cur->data, "banana") == 0)
			count++;
		cur = cur->next;
	}

	int pass = count == 2;

	free_list(a);
	if (!pass) {
		printf("    " RED "[7] Merge with duplicates failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Merge with duplicates passed\n" DEFAULT);
	return 0;
}

// Test 8: Merge long lists
int test8(void) {
	t_list *a = NULL;
	t_list *b = NULL;

	for (int i = 0; i < 10; i++) {
		char str[4];
		sprintf(str, "%03d", i * 2);  // 000, 002, ..., 018
		append_node(&a, str);
	}
	for (int i = 1; i < 20; i += 2) {
		char str[4];
		sprintf(str, "%03d", i);  // 001, 003, ..., 019
		append_node(&b, str);
	}

	ft_sorted_list_merge(&a, b, cmp_str);

	t_list *cur = a;
	char prev[4] = "";
	int pass = 1;
	while (cur) {
		if (*prev && strcmp(prev, cur->data) > 0) {
			pass = 0;
			break;
		}
		strcpy(prev, cur->data);
		cur = cur->next;
	}

	free_list(a);
	if (!pass) {
		printf("    " RED "[8] Merge long lists failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Merge long lists passed\n" DEFAULT);
	return 0;
}

// Test 9: Merge with all equal elements
int test9(void) {
	t_list *a = ft_create_elem(strdup("42"));
	a->next = ft_create_elem(strdup("42"));

	t_list *b = ft_create_elem(strdup("42"));
	b->next = ft_create_elem(strdup("42"));

	ft_sorted_list_merge(&a, b, cmp_str);

	int count = 0;
	t_list *cur = a;
	while (cur) {
		if (strcmp(cur->data, "42") == 0)
			count++;
		cur = cur->next;
	}

	int pass = count == 4;

	free_list(a);
	if (!pass) {
		printf("    " RED "[9] Merge with all equal failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Merge with all equal passed\n" DEFAULT);
	return 0;
}

// Test 10: NULL-safe merge
int test10(void) {
	int safe_cmp(void *a, void *b) {
		if (!a && !b) return 0;
		if (!a) return -1;
		if (!b) return 1;
		return strcmp((char *)a, (char *)b);
	}

	t_list *a = ft_create_elem(NULL);
	a->next = ft_create_elem(strdup("banana"));

	t_list *b = ft_create_elem(strdup("apple"));

	ft_sorted_list_merge(&a, b, safe_cmp);

	int pass = a->data == NULL &&
	           strcmp(a->next->data, "apple") == 0 &&
	           strcmp(a->next->next->data, "banana") == 0;

	free_list(a);
	if (!pass) {
		printf("    " RED "[10] NULL-safe merge failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] NULL-safe merge passed\n" DEFAULT);
	return 0;
}

