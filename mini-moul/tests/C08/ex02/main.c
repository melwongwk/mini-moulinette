#include "../../../utils/constants.h"
#include "ft_abs.h"
#include <stdio.h>

int test1(void);
int test2(void);
int test3(void);

int main(void)
{
	return (test1() + test2() + test3());
}

int test1(void)
{
	int expected = 0;
	int result = ABS(0);
	if (expected != result)
	{
		printf("    " RED "[1] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}

int test2(void)
{
	int expected = 100;
	int result = ABS(100);
	if (expected != result)
	{
		printf("    " RED "[2] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [2] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}

int test3(void)
{
	int expected = 42;
	int result = ABS(-42);
	if (expected != result)
	{
		printf("    " RED "[3] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [3] ABS() Expected %d, got %d\n"DEFAULT, expected, result);
	return (0);
}
