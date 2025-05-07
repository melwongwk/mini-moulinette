#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);

void print(int *tab, int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", tab[i]);
}

int double_func(int nbr)
{
	printf("%d ", nbr);
	return (nbr * 2);
}

int negate_func(int nbr)
{
	return -nbr;
}

int square_func(int nbr)
{
	return nbr * nbr;
}

int identity_func(int nbr)
{
	return nbr;
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

// Test 1: Basic double transform with printf side-effect
int test1(void)
{
	int tab[] = {1, 2, 3, 4, 5};
	int len = 5;
	char expected_out[] = "1 2 3 4 5 ";
	char expected_ret[] = "2 4 6 8 10 ";
	int *tab_ret;
	char *buffer, *buffer_ret;
	int saved_stdout;
	int ret = -1;

	saved_stdout = stdout_open();
	tab_ret = ft_map(tab, len, double_func);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	saved_stdout = stdout_open();
	print(tab_ret, len);
	buffer_ret = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected_out) != 0)
		printf("    " RED "[1] Expected \"%s\", got \"%s\"\n" DEFAULT, expected_out, buffer);
	else if (strcmp(buffer_ret, expected_ret) != 0)
		printf("    " RED "[1] Result tab mismatch: expected \"%s\", got \"%s\"\n" DEFAULT, expected_ret, buffer_ret);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [1] Basic double_func test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer); free(buffer_ret); free(tab_ret);
	return ret;
}

// Test 2: Negative numbers with negate_func
int test2(void)
{
	int tab[] = {-5, -1, 0, 1, 5};
	int len = 5;
	char expected[] = "5 1 0 -1 -5 ";
	int *tab_ret;
	char *buffer;
	int saved_stdout, ret = -1;

	tab_ret = ft_map(tab, len, negate_func);
	saved_stdout = stdout_open();
	print(tab_ret, len);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[2] Negate test failed: expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [2] Negate test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer); free(tab_ret);
	return ret;
}

// Test 3: Empty array input
int test3(void)
{
	int tab[] = {};
	int len = 0;
	char expected[] = "";
	int *tab_ret;
	char *buffer;
	int saved_stdout, ret = -1;

	tab_ret = ft_map(tab, len, square_func);
	saved_stdout = stdout_open();
	print(tab_ret, len);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[3] Empty array test failed: expected \"\", got \"%s\"\n" DEFAULT, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [3] Empty array test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer); free(tab_ret);
	return ret;
}

// Test 4: Ensure ft_map returns new memory (not tab itself)
int test4(void)
{
	int tab[] = {42, 21, 0};
	int len = 3;
	int *tab_ret = ft_map(tab, len, square_func);
	int ret = -1;

	if (tab_ret == tab)
		printf("    " RED "[4] Returned pointer is same as input (should be new memory)\n" DEFAULT);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [4] Output array is a fresh allocation\n" DEFAULT);
		ret = 0;
	}
	free(tab_ret);
	return ret;
}

// Test 5: Large input array
int test5(void)
{
	int tab[100];
	int len = 100;
	int *tab_ret;
	int ret = -1;
	char *buffer;
	int saved_stdout;

	for (int i = 0; i < len; i++)
		tab[i] = i;
	tab_ret = ft_map(tab, len, square_func);

	saved_stdout = stdout_open();
	print(tab_ret, 5); // check first 5 values only
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strncmp(buffer, "0 1 4 9 16", 9) != 0)
		printf("    " RED "[5] Large array test failed, got start \"%s\"\n" DEFAULT, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [5] Large input array test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer); free(tab_ret);
	return ret;
}

// Test 6: Single element array
int test6(void)
{
	int tab[] = {7};
	int len = 1;
	char expected[] = "49 ";
	int *tab_ret;
	char *buffer;
	int saved_stdout;
	int ret = -1;

	tab_ret = ft_map(tab, len, square_func);
	saved_stdout = stdout_open();
	print(tab_ret, len);
	buffer = stdout_read();
	stdout_close(saved_stdout);

	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[6] Single element test failed: expected \"%s\", got \"%s\"\n" DEFAULT, expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [6] Single element test passed\n" DEFAULT);
		ret = 0;
	}
	free(buffer); free(tab_ret);
	return ret;
}


