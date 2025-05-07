#include "../../../utils/constants.h"
#include "ft_count_if.h"
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

// Test 1: All match
int test1(void)
{
	char *tab[] = {"a", "b", "c"};
	int expected = 3;
	int result = ft_count_if(tab, 3, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[1] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] All match test passed\n" DEFAULT);
	return 0;
}

// Test 2: None match
int test2(void)
{
	char *tab[] = {"", "", ""};
	int expected = 0;
	int result = ft_count_if(tab, 3, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[2] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] None match test passed\n" DEFAULT);
	return 0;
}

// Test 3: Mixed match
int test3(void)
{
	char *tab[] = {"", "abc", "", "def"};
	int expected = 2;
	int result = ft_count_if(tab, 4, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[3] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Mixed match test passed\n" DEFAULT);
	return 0;
}

// Test 4: is_digit_string – all digits
int test4(void)
{
	char *tab[] = {"123", "456", "789"};
	int expected = 3;
	int result = ft_count_if(tab, 3, is_digit_string);
	if (result != expected)
	{
		printf("    " RED "[4] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] All digit strings match\n" DEFAULT);
	return 0;
}

// Test 5: is_digit_string – partial match
int test5(void)
{
	char *tab[] = {"123", "abc", "456", "7a8"};
	int expected = 2;
	int result = ft_count_if(tab, 4, is_digit_string);
	if (result != expected)
	{
		printf("    " RED "[5] Expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Partial digit string match\n" DEFAULT);
	return 0;
}

// Test 6: Zero length
int test6(void)
{
	char *tab[] = {"123", "abc"};
	int expected = 0;
	int result = ft_count_if(tab, 0, is_nonempty);
	if (result != expected)
	{
		printf("    " RED "[6] Zero length test failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Zero length array handled\n" DEFAULT);
	return 0;
}

// Test 7: Function always returns 0
int test7(void)
{
	char *tab[] = {"x", "y", "z"};
	int expected = 0;
	int result = ft_count_if(tab, 3, always_false);
	if (result != expected)
	{
		printf("    " RED "[7] always_false failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] always_false passed\n" DEFAULT);
	return 0;
}

// Test 8: Function always returns 1
int test8(void)
{
	char *tab[] = {"x", "y", "z"};
	int expected = 3;
	int result = ft_count_if(tab, 3, always_true);
	if (result != expected)
	{
		printf("    " RED "[8] always_true failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] always_true passed\n" DEFAULT);
	return 0;
}

// Test 9: NULL strings in array
int test9(void)
{
	char *tab[] = {NULL, "123", NULL};
	int expected = 1;
	int result = ft_count_if(tab, 3, is_digit_string);
	if (result != expected)
	{
		printf("    " RED "[9] NULL in array failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] NULL string handled correctly\n" DEFAULT);
	return 0;
}

// Test 10: Long string test
int test10(void)
{
	char *long_str = malloc(10001);
	memset(long_str, '9', 10000);
	long_str[10000] = '\0';
	char *tab[] = {"", long_str, "123", NULL};
	int expected = 2;
	int result = ft_count_if(tab, 3, is_digit_string);
	free(long_str);
	if (result != expected)
	{
		printf("    " RED "[10] Long string failed: expected %d, got %d\n" DEFAULT, expected, result);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] Long string test passed\n" DEFAULT);
	return 0;
}
