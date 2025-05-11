/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melwong <melwong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:34:04 by melwong           #+#    #+#             */
/*   Updated: 2025/05/11 21:27:15 by melwong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
t_list *ft_create_elem(void *data);
void ft_list_reverse_fun(t_list *begin_list);
void free_list(t_list *list);
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

// Test 1: Reverse 3-element string list
int test1(void) {
	t_list *list = ft_create_elem(strdup("a"));
	list->next = ft_create_elem(strdup("b"));
	list->next->next = ft_create_elem(strdup("c"));

	ft_list_reverse_fun(list);

	int pass = strcmp(list->data, "c") == 0 &&
	           strcmp(list->next->data, "b") == 0 &&
	           strcmp(list->next->next->data, "a") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Reverse string list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Reverse string list passed\n" DEFAULT);
	return 0;
}

// Test 2: Reverse 3-element integer list
int test2(void) {
	int *a = malloc(sizeof(int)); *a = 1;
	int *b = malloc(sizeof(int)); *b = 2;
	int *c = malloc(sizeof(int)); *c = 3;

	t_list *list = ft_create_elem(a);
	list->next = ft_create_elem(b);
	list->next->next = ft_create_elem(c);

	ft_list_reverse_fun(list);

	int pass = *(int *)list->data == 3 &&
	           *(int *)list->next->data == 2 &&
	           *(int *)list->next->next->data == 1;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Reverse int list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Reverse int list passed\n" DEFAULT);
	return 0;
}

// Test 3: Reverse one-element list
int test3(void) {
	t_list *list = ft_create_elem(strdup("only"));

	ft_list_reverse_fun(list);

	int pass = strcmp(list->data, "only") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] One element failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] One element passed\n" DEFAULT);
	return 0;
}

// Test 4: Reverse empty list
int test4(void) {
	t_list *list = NULL;

	ft_list_reverse_fun(list);

	printf("  " GREEN CHECKMARK GREY " [4] Empty list passed\n" DEFAULT);
	return 0;
}

// Test 5: Even number of elements
int test5(void) {
	t_list *list = ft_create_elem(strdup("1"));
	list->next = ft_create_elem(strdup("2"));
	list->next->next = ft_create_elem(strdup("3"));
	list->next->next->next = ft_create_elem(strdup("4"));

	ft_list_reverse_fun(list);

	char *expected[] = {"4", "3", "2", "1"};
	t_list *cur = list;
	int i = 0, pass = 1;
	while (cur && i < 4) {
		if (strcmp(cur->data, expected[i]) != 0) pass = 0;
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[5] Even count reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Even count reverse passed\n" DEFAULT);
	return 0;
}

// Test 6: Odd number of elements
int test6(void) {
	t_list *list = ft_create_elem(strdup("a"));
	list->next = ft_create_elem(strdup("b"));
	list->next->next = ft_create_elem(strdup("c"));
	list->next->next->next = ft_create_elem(strdup("d"));
	list->next->next->next->next = ft_create_elem(strdup("e"));

	ft_list_reverse_fun(list);

	char *expected[] = {"e", "d", "c", "b", "a"};
	t_list *cur = list;
	int i = 0, pass = 1;
	while (cur && i < 5) {
		if (strcmp(cur->data, expected[i]) != 0) pass = 0;
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[6] Odd count reverse failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Odd count reverse passed\n" DEFAULT);
	return 0;
}

// Test 7: Reverse numeric strings
int test7(void) {
	t_list *list = ft_create_elem(strdup("100"));
	list->next = ft_create_elem(strdup("200"));
	list->next->next = ft_create_elem(strdup("300"));

	ft_list_reverse_fun(list);

	char *expected[] = {"300", "200", "100"};
	t_list *cur = list;
	int i = 0, pass = 1;
	while (cur && i < 3) {
		if (strcmp(cur->data, expected[i]) != 0) pass = 0;
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[7] Numeric strings failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Numeric strings passed\n" DEFAULT);
	return 0;
}

// Test 8: Repeated values
int test8(void) {
	t_list *list = ft_create_elem(strdup("x"));
	list->next = ft_create_elem(strdup("x"));
	list->next->next = ft_create_elem(strdup("x"));

	ft_list_reverse_fun(list);

	t_list *cur = list;
	int pass = 1;
	while (cur) {
		if (strcmp(cur->data, "x") != 0) pass = 0;
		cur = cur->next;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[8] Repeated values failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Repeated values passed\n" DEFAULT);
	return 0;
}

// Test 9: NULL data in middle
int test9(void) {
	t_list *list = ft_create_elem(strdup("start"));
	list->next = ft_create_elem(NULL);
	list->next->next = ft_create_elem(strdup("end"));

	ft_list_reverse_fun(list);

	int pass = list->data && strcmp(list->data, "end") == 0 &&
	           list->next->data == NULL &&
	           list->next->next->data && strcmp(list->next->next->data, "start") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[9] NULL data in middle failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] NULL data in middle passed\n" DEFAULT);
	return 0;
}

// Test 10: Long list (10 elements)
int test10(void) {
	char *expected[] = {"10","9","8","7","6","5","4","3","2","1"};
	t_list *list = NULL, *cur = NULL;
	for (int i = 0; i < 10; i++) {
		char *val = malloc(3);
		sprintf(val, "%d", i + 1);
		t_list *node = ft_create_elem(val);
		if (!list) list = node;
		else cur->next = node;
		cur = node;
	}

	ft_list_reverse_fun(list);

	cur = list;
	int i = 0, pass = 1;
	while (cur && i < 10) {
		if (strcmp(cur->data, expected[i]) != 0) pass = 0;
		cur = cur->next;
		i++;
	}

	free_list(list);
	if (!pass) {
		printf("    " RED "[10] Long list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Long list passed\n" DEFAULT);
	return 0;
}
