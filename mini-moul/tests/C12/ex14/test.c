#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_list *ft_create_elem(void *data);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void free_list(t_list *list);
int cmp_str(void *a, void *b);
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

// Test 1: Already sorted list
int test1(void) {
	t_list *list = ft_create_elem(strdup("apple"));
	list->next = ft_create_elem(strdup("banana"));
	list->next->next = ft_create_elem(strdup("cherry"));

	ft_list_sort(&list, cmp_str);

	int pass = strcmp(list->data, "apple") == 0 &&
	           strcmp(list->next->data, "banana") == 0 &&
	           strcmp(list->next->next->data, "cherry") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Already sorted failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Already sorted passed\n" DEFAULT);
	return 0;
}

// Test 2: Reverse order list
int test2(void) {
	t_list *list = ft_create_elem(strdup("zebra"));
	list->next = ft_create_elem(strdup("monkey"));
	list->next->next = ft_create_elem(strdup("apple"));

	ft_list_sort(&list, cmp_str);

	int pass = strcmp(list->data, "apple") == 0 &&
	           strcmp(list->next->data, "monkey") == 0 &&
	           strcmp(list->next->next->data, "zebra") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Reverse order failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Reverse order passed\n" DEFAULT);
	return 0;
}

// Test 3: All equal
int test3(void) {
	char *shared = strdup("same");
	t_list *list = ft_create_elem(shared);
	list->next = ft_create_elem(strdup("same"));
	list->next->next = ft_create_elem(strdup("same"));

	ft_list_sort(&list, cmp_str);

	int pass = strcmp(list->data, "same") == 0 &&
	           strcmp(list->next->data, "same") == 0 &&
	           strcmp(list->next->next->data, "same") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] All equal failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] All equal passed\n" DEFAULT);
	return 0;
}

// Test 4: One element
int test4(void) {
	t_list *list = ft_create_elem(strdup("solo"));

	ft_list_sort(&list, cmp_str);

	int pass = list && strcmp(list->data, "solo") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[4] One element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] One element passed\n" DEFAULT);
	return 0;
}

// Test 5: Empty list
int test5(void) {
	t_list *list = NULL;

	ft_list_sort(&list, cmp_str);

	int pass = list == NULL;

	if (!pass) {
		printf("    " RED "[5] Empty list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Empty list passed\n" DEFAULT);
	return 0;
}

// Test 6: Numeric values
int test6(void) {
	int *a = malloc(sizeof(int)); *a = 42;
	int *b = malloc(sizeof(int)); *b = 7;
	int *c = malloc(sizeof(int)); *c = 19;

	t_list *list = ft_create_elem(a);
	list->next = ft_create_elem(b);
	list->next->next = ft_create_elem(c);

	ft_list_sort(&list, cmp_int);

	int pass = *(int *)list->data == 7 &&
	           *(int *)list->next->data == 19 &&
	           *(int *)list->next->next->data == 42;

	free_list(list);
	if (!pass) {
		printf("    " RED "[6] Numeric values failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Numeric values passed\n" DEFAULT);
	return 0;
}

// Test 7: Alphanumeric strings
int test7(void) {
	t_list *list = ft_create_elem(strdup("a1"));
	list->next = ft_create_elem(strdup("a10"));
	list->next->next = ft_create_elem(strdup("a2"));

	ft_list_sort(&list, cmp_str);

	int pass = strcmp(list->data, "a1") == 0 &&
	           strcmp(list->next->data, "a10") == 0 &&
	           strcmp(list->next->next->data, "a2") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[7] Alphanumeric failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Alphanumeric passed\n" DEFAULT);
	return 0;
}

int test8(void) {
	t_list *list = ft_create_elem(strdup("orange"));
	list->next = ft_create_elem(strdup("apple"));
	list->next->next = ft_create_elem(strdup("banana"));
	list->next->next->next = ft_create_elem(strdup("apple"));

	ft_list_sort(&list, cmp_str);

	char *expected[] = {"apple", "apple", "banana", "orange"};
	t_list *cur = list;
	int i = 0;
	int pass = 1;
	while (cur && i < 4) {
		if (strcmp(cur->data, expected[i]) != 0) {
			pass = 0;
			break;
		}
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[8] Duplicates intermixed failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Duplicates intermixed passed\n" DEFAULT);
	return 0;
}

int test9(void) {
	t_list *list = ft_create_elem(strdup("10"));
	list->next = ft_create_elem(strdup("2"));
	list->next->next = ft_create_elem(strdup("1"));

	ft_list_sort(&list, cmp_str);

	char *expected[] = {"1", "10", "2"};
	t_list *cur = list;
	int i = 0;
	int pass = 1;
	while (cur && i < 3) {
		if (strcmp(cur->data, expected[i]) != 0) {
			pass = 0;
			break;
		}
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[9] Numeric strings lex sort failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Numeric strings lex sort passed\n" DEFAULT);
	return 0;
}

int test10(void) {
    t_list *list = ft_create_elem(strdup("banana"));
    list->next = ft_create_elem(NULL);
    list->next->next = ft_create_elem(strdup("apple"));

    // Defensive comparison: cmp_str must guard against NULL
    int safe_cmp(void *a, void *b) {
        if (!a && !b) return 0;
        if (!a) return -1;
        if (!b) return 1;
        return strcmp((char *)a, (char *)b);
    }

    // Sort the list; expecting no crash, but correctness is not guaranteed with NULL data
    ft_list_sort(&list, safe_cmp);

    // Validate if sorting works with NULLs present; we expect the list to be ordered
    int pass = list && list->data == NULL &&
               list->next && strcmp(list->next->data, "apple") == 0 &&
               list->next->next && strcmp(list->next->next->data, "banana") == 0;

    free_list(list);
    if (!pass) {
        printf("    " RED "[10] NULL-safe sort failed\n" DEFAULT);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [10] NULL-safe sort passed\n" DEFAULT);
    return 0;
}
