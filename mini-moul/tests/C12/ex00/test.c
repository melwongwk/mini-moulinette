#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
t_list *ft_create_elem(void *data);

// Test declarations
int test1(void);
int test2(void);
int test3(void);

int main(void) {
	int result = 0;

	if (test1() != 0) result = -1;
	if (test2() != 0) result = -1;
	if (test3() != 0) result = -1;

	return result;
}

// Tests

int test1(void) {
	char *str = "Hello";
	t_list *elem = ft_create_elem(str);

	if (!elem || elem->data != str || elem->next != NULL) {
		printf("    " RED "[1] Basic element creation failed\n" DEFAULT);
		free(elem);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Basic element creation passed\n" DEFAULT);
	free(elem);
	return 0;
}

int test2(void) {
	int num = 42;
	t_list *elem = ft_create_elem(&num);

	if (!elem || *(int *)(elem->data) != 42 || elem->next != NULL) {
		printf("    " RED "[2] Integer data element creation failed\n" DEFAULT);
		free(elem);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Integer data element creation passed\n" DEFAULT);
	free(elem);
	return 0;
}

int test3(void) {
	t_list *elem = ft_create_elem(NULL);

	if (!elem || elem->data != NULL || elem->next != NULL) {
		printf("    " RED "[3] NULL data element creation failed\n" DEFAULT);
		free(elem);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] NULL data element creation passed\n" DEFAULT);
	free(elem);
	return 0;
}
