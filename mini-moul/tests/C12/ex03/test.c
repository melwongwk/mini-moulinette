#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void   ft_list_push_front(t_list **begin_list, void *data);
t_list *ft_list_last(t_list *begin_list);

// Test declarations
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);


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

// Test 1: Last element in a single-element list
int test1(void) {
	t_list *list = ft_create_elem("Only");

	t_list *last = ft_list_last(list);
	if (!last || strcmp((char *)last->data, "Only") != 0) {
		printf("    " RED "[1] Single-element list failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Single-element list passed\n" DEFAULT);
	free(list);
	return 0;
}

// Test 2: Last element in a multi-element list
int test2(void) {
	t_list *list = NULL;
	ft_list_push_front(&list, "Third");
	ft_list_push_front(&list, "Second");
	ft_list_push_front(&list, "First");

	t_list *last = ft_list_last(list);
	if (!last || strcmp((char *)last->data, "Third") != 0) {
		printf("    " RED "[2] Multi-element list failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Multi-element list passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

// Test 3: Empty list
int test3(void) {
	t_list *list = NULL;

	t_list *last = ft_list_last(list);
	if (last != NULL) {
		printf("    " RED "[3] Empty list failed (expected NULL)\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Empty list passed\n" DEFAULT);
	return 0;
}

int test4(void) {
	t_list *list = NULL;

	ft_list_push_front(&list, NULL);
	ft_list_push_front(&list, "Hello");
	ft_list_push_front(&list, "Start");

	t_list *last = ft_list_last(list);
	if (!last || last->data != NULL) {
		printf("    " RED "[4] List with NULL data in last node failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] List with NULL data in last node passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

int test5(void) {
	int number = 42;
	double pi = 3.14;
	t_list *list = NULL;

	ft_list_push_front(&list, &pi);
	ft_list_push_front(&list, &number);
	ft_list_push_front(&list, "Start");

	t_list *last = ft_list_last(list);
	if (!last || *((double *)last->data) != 3.14) {
		printf("    " RED "[5] Mixed data types in list failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Mixed data types in list passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

int test6(void) {
	t_list *list = NULL;
	char *last_val = "End";

	// Create 1000 nodes
	ft_list_push_front(&list, last_val);        // Add "End" first
	for (int i = 0; i < 999; i++) {
		ft_list_push_front(&list, "Fill");  // Add "Fill" nodes in front
	}

	t_list *last = ft_list_last(list);
	if (!last || strcmp((char *)last->data, last_val) != 0) {
		printf("    " RED "[6] Long list failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Long list passed\n" DEFAULT);
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

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*new_elem;

	new_elem = ft_create_elem(data);
	if (!new_elem)
		return ;
	new_elem->next = *begin_list;
	*begin_list = new_elem;
}
