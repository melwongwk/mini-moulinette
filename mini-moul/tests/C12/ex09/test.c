#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_foreach(t_list *begin_list, void (*f)(void *));
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
	for (int i = 0; str[i]; ++i) {
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

void append_x(void *data) {
	char *str = data;
	size_t len = strlen(str);
	if (len < 255)
		str[len] = 'x', str[len + 1] = '\0';
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

// Test 1: Apply to_uppercase to 3 strings
int test1(void) {
	t_list *list = ft_create_elem(strdup("hello"));
	list->next = ft_create_elem(strdup("world"));
	list->next->next = ft_create_elem(strdup("test"));

	ft_list_foreach(list, to_uppercase);

	int pass = strcmp(list->data, "HELLO") == 0 &&
	           strcmp(list->next->data, "WORLD") == 0 &&
	           strcmp(list->next->next->data, "TEST") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[1] Uppercase conversion failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Uppercase conversion passed\n" DEFAULT);
	return 0;
}

// Test 2: Apply append_x to each element
int test2(void) {
	t_list *list = ft_create_elem(strdup("a"));
	list->next = ft_create_elem(strdup("b"));
	list->next->next = ft_create_elem(strdup("c"));

	ft_list_foreach(list, append_x);

	int pass = strcmp(list->data, "ax") == 0 &&
	           strcmp(list->next->data, "bx") == 0 &&
	           strcmp(list->next->next->data, "cx") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[2] Append x failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Append x passed\n" DEFAULT);
	return 0;
}

// Test 3: Apply to single element
int test3(void) {
	t_list *list = ft_create_elem(strdup("solo"));
	ft_list_foreach(list, to_uppercase);

	int pass = strcmp(list->data, "SOLO") == 0;

	free_list(list);
	if (!pass) {
		printf("    " RED "[3] Single-element function apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Single-element function apply passed\n" DEFAULT);
	return 0;
}

// Test 4: Apply to NULL list
int test4(void) {
	t_list *list = NULL;
	ft_list_foreach(list, to_uppercase);
	printf("  " GREEN CHECKMARK GREY " [4] NULL list handled gracefully\n" DEFAULT);
	return 0;
}

// Test 5: Apply to a long list
int test5(void) {
	t_list *head = NULL;
	t_list *current = NULL;
	char buffer[10][8];
	for (int i = 0; i < 10; ++i) {
		snprintf(buffer[i], sizeof(buffer[i]), "a%d", i);
		t_list *new_elem = ft_create_elem(strdup(buffer[i]));
		if (!head)
			head = new_elem;
		else
			current->next = new_elem;
		current = new_elem;
	}

	ft_list_foreach(head, append_x);

	int pass = 1;
	current = head;
	for (int i = 0; i < 10 && current; ++i) {
		char expected[8];
		snprintf(expected, sizeof(expected), "a%dx", i);
		if (strcmp(current->data, expected) != 0)
			pass = 0;
		current = current->next;
	}

	free_list(head);
	if (!pass) {
		printf("    " RED "[5] Long list apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Long list apply passed\n" DEFAULT);
	return 0;
}

// Test 6: Shared data pointer
int test6(void) {
	char *shared = strdup("same");
	t_list *list = ft_create_elem(shared);
	list->next = ft_create_elem(shared);
	list->next->next = ft_create_elem(shared);

	ft_list_foreach(list, to_uppercase);

	int pass = strcmp(shared, "SAME") == 0;

	free(list->next->next);
	free(list->next);
	free(list);
	free(shared);

	if (!pass) {
		printf("    " RED "[6] Shared data pointer apply failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Shared data pointer apply passed\n" DEFAULT);
	return 0;
}
