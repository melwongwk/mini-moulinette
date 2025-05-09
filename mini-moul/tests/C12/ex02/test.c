#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int ft_list_size(t_list *begin_list);
t_list *ft_create_elem(void *data);
void ft_list_push_front(t_list **begin_list, void *data);

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

// Test 1: Size of an empty list
int test1(void) {
	t_list *list = NULL;

	if (ft_list_size(list) != 0) {
		printf("    " RED "[1] Size of empty list failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Size of empty list passed\n" DEFAULT);
	return 0;
}

// Test 2: Size of a single-element list
int test2(void) {
	t_list *list = NULL;
	char *data = "Only one";

	ft_list_push_front(&list, data);

	if (ft_list_size(list) != 1) {
		printf("    " RED "[2] Size of single-element list failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Size of single-element list passed\n" DEFAULT);
	free(list);
	return 0;
}

// Test 3: Size of a multi-element list
int test3(void) {
	t_list *list = NULL;
	ft_list_push_front(&list, "Third");
	ft_list_push_front(&list, "Second");
	ft_list_push_front(&list, "First");

	if (ft_list_size(list) != 3) {
		printf("    " RED "[3] Size of multi-element list failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Size of multi-element list passed\n" DEFAULT);

	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

int test4(void) {
	t_list *list = NULL;

	ft_list_push_front(&list, NULL);
	ft_list_push_front(&list, "Data");
	ft_list_push_front(&list, NULL);

	if (ft_list_size(list) != 3) {
		printf("    " RED "[4] Mixed NULL and non-NULL data count failed\n" DEFAULT);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Mixed NULL and non-NULL data count passed\n" DEFAULT);
	while (list) {
		t_list *tmp = list;
		list = list->next;
		free(tmp);
	}
	return 0;
}

int test5(void) {
	t_list *list = NULL;
	ft_list_push_front(&list, "C");
	ft_list_push_front(&list, "B");
	ft_list_push_front(&list, "A");

	// Artificial mutation: break list in middle
	if (list && list->next)
		list->next = NULL;

	int size = ft_list_size(list);
	if (size != 1) {
		printf("    " RED "[5] List size after mutation failed (got %d, expected 1)\n" DEFAULT, size);
		while (list) {
			t_list *tmp = list;
			list = list->next;
			free(tmp);
		}
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] List size after mutation passed\n" DEFAULT);

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