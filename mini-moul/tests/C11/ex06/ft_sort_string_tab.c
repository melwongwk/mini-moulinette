#include "../../../utils/constants.h"
#include "ft_sort_string_tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Helpers
int tab_equals(char **a, char **b) {
	for (int i = 0; a[i] && b[i]; i++) {
		if (strcmp(a[i], b[i]) != 0)
			return 0;
	}
	return (a[0] == NULL && b[0] == NULL) || (a[0] != NULL && b[0] != NULL);
}

char **copy_tab(char **src) {
	int len = 0;
	while (src[len]) len++;

	char **copy = malloc((len + 1) * sizeof(char *));
	for (int i = 0; i < len; i++)
		copy[i] = strdup(src[i]);
	copy[len] = NULL;
	return copy;
}

void free_tab(char **tab) {
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

// Test declarations
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

// Test cases

int test1(void) {
	char *input[] = {"banana", "apple", "cherry", NULL};
	char *expected[] = {"apple", "banana", "cherry", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[1] Simple sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Simple sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test2(void) {
	char *input[] = {"z", "x", "y", NULL};
	char *expected[] = {"x", "y", "z", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[2] Reverse alphabetical failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Reverse alphabetical passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test3(void) {
	char *input[] = {"abc", "Abc", "aBc", NULL};
	char *expected[] = {"Abc", "aBc", "abc", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[3] Case-sensitive sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Case-sensitive sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test4(void) {
	char *input[] = {"one", "two", "three", "four", "five", NULL};
	char *expected[] = {"five", "four", "one", "three", "two", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[4] Larger input failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Larger input passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test5(void) {
	char *input[] = {NULL};
	char *expected[] = {NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[5] Empty tab failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Empty tab passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test6(void) {
	char *input[] = {"42", NULL};
	char *expected[] = {"42", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[6] One-element tab failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] One-element tab passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test7(void) {
	char *input[] = {"abc", "abc", "abc", NULL};
	char *expected[] = {"abc", "abc", "abc", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[7] Duplicate values failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Duplicate values passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test8(void) {
	char *input[] = {"", "a", "", "b", NULL};
	char *expected[] = {"", "", "a", "b", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[8] Empty strings failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Empty strings passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test9(void) {
	char *input[] = {"1", "!", "A", "a", NULL};
	char *expected[] = {"!", "1", "A", "a", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[9] ASCII order test failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] ASCII order passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test10(void) {
	char *input[] = {"abcd", "abc", "ab", "a", NULL};
	char *expected[] = {"a", "ab", "abc", "abcd", NULL};
	char **tab = copy_tab(input);
	ft_sort_string_tab(tab);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[10] Prefix order test failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Prefix order passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}
