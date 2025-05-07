#include "../../../utils/constants.h"
#include "ft_is_sort.h"
#include <stdio.h>

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

// Comparison function: ascending order
int cmp_asc(int a, int b)
{
	return (a - b);
}

// Comparison function: descending order
int cmp_desc(int a, int b)
{
	return (b - a);
}

// Comparison function: always zero
int cmp_equal(int a, int b)
{
	(void)a;
	(void)b;
	return 0;
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

// Test 1: Sorted ascending
int test1(void)
{
	int tab[] = {1, 2, 3, 4, 5};
	if (!ft_is_sort(tab, 5, cmp_asc))
	{
		printf("    " RED "[1] Expected sorted ascending\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [1] Sorted ascending passed\n" DEFAULT);
	return 0;
}

// Test 2: Sorted descending
int test2(void)
{
	int tab[] = {5, 4, 3, 2, 1};
	if (!ft_is_sort(tab, 5, cmp_desc))
	{
		printf("    " RED "[2] Expected sorted descending\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [2] Sorted descending passed\n" DEFAULT);
	return 0;
}

// Test 3: Not sorted
int test3(void)
{
	int tab[] = {1, 3, 2, 4};
	if (ft_is_sort(tab, 4, cmp_asc))
	{
		printf("    " RED "[3] Should not be sorted\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [3] Not sorted passed\n" DEFAULT);
	return 0;
}

// Test 4: All elements equal
int test4(void)
{
	int tab[] = {7, 7, 7, 7};
	if (!ft_is_sort(tab, 4, cmp_asc))
	{
		printf("    " RED "[4] Equal elements should be sorted\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [4] Equal elements sorted passed\n" DEFAULT);
	return 0;
}

// Test 5: Two elements sorted
int test5(void)
{
	int tab[] = {1, 2};
	if (!ft_is_sort(tab, 2, cmp_asc))
	{
		printf("    " RED "[5] Two elements ascending failed\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [5] Two elements ascending passed\n" DEFAULT);
	return 0;
}

// Test 6: Two elements not sorted
int test6(void)
{
	int tab[] = {2, 1};
	if (ft_is_sort(tab, 2, cmp_asc))
	{
		printf("    " RED "[6] Two elements descending should not pass for ascending cmp\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [6] Two elements descending rejected correctly\n" DEFAULT);
	return 0;
}

// Test 7: One element (always sorted)
int test7(void)
{
	int tab[] = {42};
	if (!ft_is_sort(tab, 1, cmp_asc))
	{
		printf("    " RED "[7] One element should always be sorted\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [7] One element passed\n" DEFAULT);
	return 0;
}

// Test 8: Zero-length array
int test8(void)
{
	int tab[] = {0};
	if (!ft_is_sort(tab, 0, cmp_asc))
	{
		printf("    " RED "[8] Zero length array should be sorted\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [8] Zero-length array handled\n" DEFAULT);
	return 0;
}

// Test 9: Alternating values (not sorted)
int test9(void)
{
	int tab[] = {1, 3, 2, 4, 3};
	if (ft_is_sort(tab, 5, cmp_asc))
	{
		printf("    " RED "[9] Alternating values should not be sorted\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [9] Alternating values rejected\n" DEFAULT);
	return 0;
}

// Test 10: Comparison function always returns 0
int test10(void)
{
	int tab[] = {5, 1, 99, -100, 3};
	if (!ft_is_sort(tab, 5, cmp_equal))
	{
		printf("    " RED "[10] cmp_equal should return sorted always\n" DEFAULT);
		return -1;
	}
	printf("  " GREEN CHECKMARK GREY " [10] cmp_equal passed\n" DEFAULT);
	return 0;
}
