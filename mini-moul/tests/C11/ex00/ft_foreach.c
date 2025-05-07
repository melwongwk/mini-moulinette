#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_foreach.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);

void func1(int nbr) // Prints number with a space
{
	printf("%d ", nbr);
}

void func2(int nbr) // Prints double the number
{
	printf("%d ", nbr * 2);
}

int main(void)
{
	int result = 0;

	if (test1() != 0)
		result = -1;
	if (test2() != 0)
		result = -1;
	if (test3() != 0)
		result = -1;
	if (test4() != 0)
		result = -1;
	if (test5() != 0)
		result = -1;
	if (test6() != 0)
		result = -1;

	return result;
}

// Test 1: Basic test
int test1(void)
{
	int tab[] = {1, 2, 3, 4, 5};
	char expected[] = "1 2 3 4 5 ";
	char *buffer;
	int saved_stdout;
	int ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, sizeof(tab) / sizeof(tab[0]), func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[1] ft_foreach({1,2,3,4,5}, 5, func1) Expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [1] ft_foreach({1,2,3,4,5}, 5, func1) output \"%s\" as expected\n" DEFAULT, buffer);
		ret = 0;
	}
	free(buffer);
	return ret;
}

// Test 2: Doubled output
int test2(void)
{
	int tab[] = {1, 2, 3};
	char expected[] = "2 4 6 ";
	char *buffer;
	int saved_stdout;
	int ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, 3, func2);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[2] ft_foreach({1,2,3}, 3, func2) Expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [2] ft_foreach({1,2,3}, 3, func2) output \"%s\" as expected\n" DEFAULT, buffer);
		ret = 0;
	}
	free(buffer);
	return ret;
}

// Test 3: Negative and zero
int test3(void)
{
	int tab[] = {-2, 0, 2};
	char expected[] = "-2 0 2 ";
	char *buffer;
	int saved_stdout;
	int ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, 3, func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[3] ft_foreach({-2,0,2}, 3, func1) Expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [3] ft_foreach({-2,0,2}, 3, func1) output \"%s\" as expected\n" DEFAULT, buffer);
		ret = 0;
	}
	free(buffer);
	return ret;
}

// Test 4: Empty array
int test4(void)
{
	int tab[] = {};
	char expected[] = "";
	char *buffer;
	int saved_stdout;
	int ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, 0, func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[4] ft_foreach({}, 0, func1) Expected empty output, got \"%s\"\n" DEFAULT, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [4] ft_foreach({}, 0, func1) output empty string as expected\n" DEFAULT);
		ret = 0;
	}
	free(buffer);
	return ret;
}

// Test 5: Large array
int test5(void)
{
	int tab[100];
	char expected[400] = "";
	for (int i = 0; i < 100; i++) {
		tab[i] = i;
		char tmp[5];
		sprintf(tmp, "%d ", i);
		strcat(expected, tmp);
	}
	char *buffer;
	int saved_stdout, ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, 100, func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[5] Large array failed.\n" DEFAULT);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [5] Large array processed successfully\n" DEFAULT);
		ret = 0;
	}
	free(buffer);
	return ret;
}

// Test 6: Single-element array
int test6(void)
{
	int tab[] = {99};
	char expected[] = "99 ";
	char *buffer;
	int saved_stdout, ret = -1;

	saved_stdout = stdout_open();
	ft_foreach(tab, 1, func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[6] Single-element test failed: expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [6] Single-element test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer);
	return ret;
}
