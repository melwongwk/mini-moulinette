#include "../../../utils/constants.h"
#include "ft_any.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int is_nonempty(char *str)
{
	return (str && str[0] != '\0');
}

int is_digit_string(char *str)
{
	if (!str || !*str)
		return 0;
	for (int i = 0; str[i]; i++)
		if (str[i] < '0' || str[i] > '9')
			return 0;
	return 1;
}

int always_false(char *str)
{
	(void)str;
	return 0;
}

int always_true(char *str)
{
	(void)str;
	return 1;
}

int main(void)
{
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

// Test 1: At least one non-empty string
int test1(void)
{
	char *tab[] = {"", "hello", "world", NULL};
	int expected = 1;
	int result = ft_any(tab, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[1] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Basic non-empty check passed\n" DEFAULT);
	return 0;
}

// Test 2: All empty strings
int test2(void)
{
	char *tab[] = {"", "", "", NULL};
	int expected = 0;
	int result = ft_any(tab, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[2] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] All empty strings test passed\n" DEFAULT);
	return 0;
}

// Test 3: First string triggers return
int test3(void)
{
	char *tab[] = {"hello", "", "", NULL};
	int expected = 1;
	int result = ft_any(tab, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[3] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Early match test passed\n" DEFAULT);
	return 0;
}

// Test 4: No match at all
int test4(void)
{
	char *tab[] = {"abc", "xyz", "12a", NULL};
	int expected = 0;
	int result = ft_any(tab, is_digit_string);
	if (result != expected)
	{
		printf("    " RED "[4] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] No matches test passed\n" DEFAULT);
	return 0;
}

// Test 5: One string matches (all digits)
int test5(void)
{
	char *tab[] = {"abc", "123", "xyz", NULL};
	int expected = 1;
	int result = ft_any(tab, is_digit_string);
	if (result != expected)
	{
		printf("    " RED "[5] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Digit string match passed\n" DEFAULT);
	return 0;
}

// Test 6: Empty array (first element NULL)
int test6(void)
{
	char *tab[] = {NULL};
	int expected = 0;
	int result = ft_any(tab, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[6] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Empty array handled\n" DEFAULT);
	return 0;
}

// Test 7: Early NULL in array
int test7(void)
{
	char *tab[] = {"abc", NULL, "def", NULL};
	int expected = 1;
	int result = ft_any(tab, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[7] Early NULL in array failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] Early NULL in array handled\n" DEFAULT);
	return 0;
}

// Test 8: Function always returns 0
int test8(void)
{
	char *tab[] = {"something", "another", "yetanother", NULL};
	int expected = 0;
	int result = ft_any(tab, always_false);
	if (result != expected)
	{
		printf("    " RED "[8] always_false function test failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] always_false test passed\n" DEFAULT);
	return 0;
}

// Test 9: Function always returns 1
int test9(void)
{
	char *tab[] = {"", "", "", NULL};
	int expected = 1;
	int result = ft_any(tab, always_true);
	if (result != expected)
	{
		printf("    " RED "[9] always_true function test failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] always_true test passed\n" DEFAULT);
	return 0;
}

// Test 10: Very long string
int test10(void)
{
	char *long_str = malloc(10001);
	memset(long_str, 'a', 10000);
	long_str[10000] = '\0';
	char *tab[] = {"", long_str, NULL};
	int expected = 1;
	int result = ft_any(tab, is_nonempty);
	free(long_str);

	if (result != expected)
	{
		printf("    " RED "[10] Long string test failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Long string test passed\n" DEFAULT);
	return 0;
}
