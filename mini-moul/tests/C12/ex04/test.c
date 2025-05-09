#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_push_back(t_list **begin_list, void *data);
t_list *ft_list_last(t_list *begin_list);

// Test declarations
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);

int main(void) {
	int result = 0;

	if (test1() != 0) result = -1;
	if (test2() != 0) result = -1;
	if (test3() != 0) result = -1;
	if (test4() != 0) result = -1;
	if (test5() != 0) result = -1;

	return result;
}

// Tests

int test1(void) {
	t_list *list = NULL;
	char *str = "Hello";

	ft_list_push_back(&list, str);
	if (!list || list->data != str || list->next != NULL) {
		printf("    " RED "[1] Push to empty list failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Push to empty list passed\n" DEFAULT);
	free(list);
	return 0;
}

int test2(void) {
	t_list *list = ft_create_elem("Start");
	char *end = "End";

	ft_list_push_back(&list, end);
	if (!list || !list->next || strcmp((char *)list->next->data, end) != 0) {
		printf("    " RED "[2] Push to non-empty list failed\n" DEFAULT);
		free(list->next);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Push to non-empty list passed\n" DEFAULT);
	free(list->next);
	free(list);
	return 0;
}

int test3(void) {
	t_list *list = ft_create_elem("One");
	ft_list_push_back(&list, "Two");
	ft_list_push_back(&list, "Three");

	t_list *last = ft_list_last(list);
	if (!last || strcmp((char *)last->data, "Three") != 0) {
		printf("    " RED "[3] Push multiple elements failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Push multiple elements passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

int test4(void) {
	t_list *list = NULL;

	ft_list_push_back(&list, NULL);
	if (!list || list->data != NULL || list->next != NULL) {
		printf("    " RED "[4] Push NULL data failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Push NULL data passed\n" DEFAULT);
	free(list);
	return 0;
}

int test5(void) {
	t_list *list = NULL;
	int n = 42;
	char *s = "Test";

	ft_list_push_back(&list, &n);
	ft_list_push_back(&list, s);

	t_list *first = list;
	t_list *second = list->next;

	if (!first || !second || *(int *)(first->data) != 42 || strcmp((char *)second->data, "Test") != 0) {
		printf("    " RED "[5] Push mixed data types failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Push mixed data types passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}


t_list	*ft_create_elem(void *data)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->next = NULL;
	return (elem);
}
