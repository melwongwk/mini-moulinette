#include "../../../utils/constants.h"
#include "ft_abs.h"
#include <stdio.h>
#include <limits.h>

int test1(void);
int test2(void);
int test3(void);
int	test4(void);
int	test5(void);
int	test6(void);

int main(void)
{
	return (
		test1() + test2() + test3() +
		test4() + test5() + test6()
	);
}

int test1(void)
{
	int expected = 0;
	int result = ABS(0);
	if (expected != result)
	{
		printf("    " RED "[1] ABS(0) Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ABS(0) Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}

int test2(void)
{
	int expected = 100;
	int result = ABS(100);
	if (expected != result)
	{
		printf("    " RED "[2] ABS(100) Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ABS(100) Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}

int test3(void)
{
	int expected = 42;
	int result = ABS(-42);
	if (expected != result)
	{
		printf("    " RED "[3] ABS(-42) Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] ABS(-42) Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}

int test4(void)
{
	int expected = 0;
	int result = ABS(-0);
	if (expected != result)
	{
		printf("    " RED "[4] ABS(-0) Expected %d, got %d\n" DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [4] ABS(-0) Expected %d, got %d\n" DEFAULT, expected, result);
	return (0);
}

int test5(void)
{
	int expected = INT_MAX;
	int result = ABS(INT_MAX);
	if (expected != result)
	{
		printf("    " RED "[5] ABS(INT_MAX) Expected %d, got %d\n" DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [5] ABS(INT_MAX) Expected %d, got %d\n" DEFAULT, expected, result);
	return (0);
}

int test6(void)
{
	int expected = 1;
	int result = ABS(1 - 2);
	if (expected != result)
	{
		printf("    " RED "[6] ABS(1 - 2) Expected %d, got %d\n" DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [6] ABS(1 - 2) Expected %d, got %d\n" DEFAULT, expected, result);
	return (0);
}
