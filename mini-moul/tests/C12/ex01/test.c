#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void ft_list_push_front(t_list **begin_list, void *data);
t_list *ft_create_elem(void *data);

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

// Test pushing a single element into an empty list
int test1(void) {
	t_list *list = NULL;
	char *str = "Front";

	ft_list_push_front(&list, str);

	if (!list || list->data != str || list->next != NULL) {
		printf("    " RED "[1] Push front into empty list failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Push front into empty list passed\n" DEFAULT);
	free(list);
	return 0;
}

// Test pushing multiple elements and checking order
int test2(void) {
	t_list *list = NULL;
	char *second = "Second";
	char *first = "First";

	ft_list_push_front(&list, second);
	ft_list_push_front(&list, first);

	if (!list || list->data != first || !list->next || list->next->data != second || list->next->next != NULL) {
		printf("    " RED "[2] Push front with multiple elements failed\n" DEFAULT);
		free(list->next);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Push front with multiple elements passed\n" DEFAULT);
	free(list->next);
	free(list);
	return 0;
}

// Test pushing NULL data
int test3(void) {
	t_list *list = NULL;

	ft_list_push_front(&list, NULL);

	if (!list || list->data != NULL || list->next != NULL) {
		printf("    " RED "[3] Push front with NULL data failed\n" DEFAULT);
		free(list);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Push front with NULL data passed\n" DEFAULT);
	free(list);
	return 0;
}

// Long List Push
int test4(void) {
	t_list *list = NULL;
	const int size = 100;
	char buffer[32];
	int success = 1;

	for (int i = 0; i < size; i++) {
		sprintf(buffer, "Element %d", i);
		char *data = strdup(buffer);  // Duplicate so each has separate memory
		if (!data) return -1;
		ft_list_push_front(&list, data);
	}

	// Traverse list to ensure all elements are present and in reverse order
	for (int i = size - 1; i >= 0; i--) {
		sprintf(buffer, "Element %d", i);
		if (!list || strcmp((char *)list->data, buffer) != 0) {
			printf("    " RED "[4] Long list element order mismatch at index %d\n" DEFAULT, i);
			success = 0;
			break;
		}
		t_list *tmp = list;
		list = list->next;
		free(tmp->data); // free strdup'd data
		free(tmp);
	}

	if (success && list == NULL) {
		printf("  " GREEN CHECKMARK GREY " [4] Long list push front passed\n" DEFAULT);
		return 0;
	}
	if (list != NULL) {
		printf("    " RED "[4] List not fully freed\n" DEFAULT);
	}
	return -1;
}

// Mixed Data Types
int test5(void) {
	t_list *list = NULL;

	int num = 123;
	double pi = 3.14;
	char *msg = "Hello";

	ft_list_push_front(&list, msg);
	ft_list_push_front(&list, &pi);
	ft_list_push_front(&list, &num);

	if (!list || *(int *)list->data != 123) {
		printf("    " RED "[5] Integer data check failed\n" DEFAULT);
		return -1;
	}
	list = list->next;
	if (!list || *(double *)list->data != 3.14) {
		printf("    " RED "[5] Double data check failed\n" DEFAULT);
		return -1;
	}
	list = list->next;
	if (!list || (char *)list->data != msg) {
		printf("    " RED "[5] Char* data check failed\n" DEFAULT);
		return -1;
	}
	list = list->next;
	if (list != NULL) {
		printf("    " RED "[5] List should end but does not\n" DEFAULT);
		return -1;
	}

	printf("  " GREEN CHECKMARK GREY " [5] Mixed data types push front passed\n" DEFAULT);
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
