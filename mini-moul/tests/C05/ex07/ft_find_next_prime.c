#include <stdio.h>
#include "../../../../ex07/ft_find_next_prime.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int n;
    int expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
		{
			.desc = "Next prime after a large negative number",
			.n = -2147483648,
			.expected = 2,
		},
		{
			.desc = "Next prime after a negative number",
			.n = -5,
			.expected = 2,
		},
		{
			.desc = "Next prime after 0",
			.n = 0,
			.expected = 2,
		},
		{
			.desc = "Next prime after 1",
			.n = 1,
			.expected = 2,
		},
		{
			.desc = "Next prime after 2",
			.n = 2,
			.expected = 2,
		},
		{
			.desc = "Next prime after 3",
			.n = 3,
			.expected = 3,
		},
		{
			.desc = "Next prime after 4",
			.n = 4,
			.expected = 5,
		},
		{
			.desc = "Next prime after 10",
			.n = 10,
			.expected = 11,
		},
		{
			.desc = "Next prime after 13",
			.n = 13,
			.expected = 13,
		},
		{
			.desc = "Next prime after 14",
			.n = 14,
			.expected = 17,
		},
		{
			.desc = "Next prime after 20",
			.n = 20,
			.expected = 23,
		},
		{
			.desc = "Next prime after 24",
			.n = 24,
			.expected = 29,
		},
		{
			.desc = "Next prime after 100",
			.n = 100,
			.expected = 101,
		},
		{
			.desc = "Next prime after 169 (13 * 13)",
			.n = 169,
			.expected = 173,
		},
		{
			.desc = "Next prime after 200",
			.n = 200,
			.expected = 211,
		},
		{
			.desc = "Next prime after 899 (29 * 31)",
			.n = 899,
			.expected = 907,
		},
		{
			.desc = "Next prime after 997",
			.n = 997,
			.expected = 997,
		},
		{
			.desc = "Next prime after 1000",
			.n = 1000,
			.expected = 1009,
		},
		{
			.desc = "Next prime after 2147483630",
			.n = 2147483630,
			.expected = 2147483647,
		},
		{
			.desc = "Next prime after 2147483647",
			.n = 2147483647,
			.expected = 2147483647,
		},
	};
    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        int result = ft_find_next_prime(tests[i].n);

        if (result != tests[i].expected)
        {
            printf("    " RED "[%d] %s Expected %d, got %d\n", i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
        {
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);
        }
    }

    return error;
}
