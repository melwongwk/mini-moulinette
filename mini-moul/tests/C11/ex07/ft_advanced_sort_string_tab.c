#include "../../../utils/constants.h"
#include "ft_advanced_sort_string_tab.h"
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

// Comparators
int ascii_cmp(char *a, char *b) {
	return strcmp(a, b);
}

int rev_ascii_cmp(char *a, char *b) {
	return -strcmp(a, b);
}

int len_cmp(char *a, char *b) {
	return strlen(a) - strlen(b);
}

int alphabetical_then_length(char *a, char *b) {
	int cmp = strcmp(a, b);
	if (cmp != 0)
		return cmp;
	return strlen(a) - strlen(b);
}

int length_then_alphabetical(char *a, char *b) {
	int len_cmp = strlen(a) - strlen(b);
	if (len_cmp != 0)
		return len_cmp;
	return strcmp(a, b);
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

// Tests

int test1(void) {
	char *input[] = {"banana", "apple", "cherry", NULL};
	char *expected[] = {"apple", "banana", "cherry", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[1] ASCII sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] ASCII sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test2(void) {
	char *input[] = {"banana", "apple", "cherry", NULL};
	char *expected[] = {"cherry", "banana", "apple", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, rev_ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[2] Reverse ASCII sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Reverse ASCII sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test3(void) {
	char *input[] = {"banana", "fig", "apple", "kiwi", NULL};
	char *expected[] = {"fig", "kiwi", "apple", "banana", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, len_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[3] Length sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Length sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test4(void) {
	char *input[] = {NULL};
	char *expected[] = {NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[4] Empty tab failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Empty tab passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test5(void) {
	char *input[] = {"same", "same", "same", NULL};
	char *expected[] = {"same", "same", "same", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[5] Equal elements failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Equal elements passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test6(void) {
	char *input[] = {"a", "ab", "abc", "abcd", NULL};
	char *expected[] = {"abcd", "abc", "ab", "a", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, rev_ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[6] Reverse ASCII on prefix strings failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Reverse ASCII on prefix strings passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test7(void) {
	char *input[] = {"a", "bbb", "cc", "dddd", NULL};
	char *expected[] = {"a", "cc", "bbb", "dddd", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, length_then_alphabetical);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[7] Length then alphabetical failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Length then alphabetical passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test8(void) {
	char *input[] = {"abc", "Abc", "aBc", NULL};
	char *expected[] = {"Abc", "aBc", "abc", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[8] Case-sensitive ASCII sort failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Case-sensitive ASCII sort passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test9(void) {
	char *input[] = {"", "a", "", "b", NULL};
	char *expected[] = {"", "", "a", "b", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, ascii_cmp);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[9] Sort with empty strings failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Sort with empty strings passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}

int test10(void) {
	char *input[] = {"abc", "abcd", "abc", "ab", NULL};
	char *expected[] = {"ab", "abc", "abc", "abcd", NULL};
	char **tab = copy_tab(input);
	ft_advanced_sort_string_tab(tab, alphabetical_then_length);
	if (!tab_equals(tab, expected)) {
		printf("    " RED "[10] Alphabetical then length failed\n" DEFAULT);
		free_tab(tab);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Alphabetical then length passed\n" DEFAULT);
	free_tab(tab);
	return 0;
}
