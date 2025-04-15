#include <stdio.h>
#include "../../../../ex06/ft_is_prime.c"
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
        .desc = "Is -5 prime",
        .n = -5,
        .expected = 0,
    },
    {
        .desc = "Is 0 prime",
        .n = 0,
        .expected = 0,
    },
    {
        .desc = "Is 1 prime",
        .n = 1,
        .expected = 0,
    },
    {
        .desc = "Is 2 prime",
        .n = 2,
        .expected = 1,
    },
    {
        .desc = "Is 3 prime",
        .n = 3,
        .expected = 1,
    },
    {
        .desc = "Is 4 prime",
        .n = 4,
        .expected = 0,
    },
    {
        .desc = "Is 7 prime",
        .n = 7,
        .expected = 1,
    },
    {
        .desc = "Is 11 prime",
        .n = 11,
        .expected = 1,
    },
    {
        .desc = "Is 13 prime",
        .n = 13,
        .expected = 1,
    },
    {
        .desc = "Is 17 prime",
        .n = 17,
        .expected = 1,
    },
    {
        .desc = "Is 19 prime",
        .n = 19,
        .expected = 1,
    },
    {
        .desc = "Is 23 prime",
        .n = 23,
        .expected = 1,
    },
    {
        .desc = "Is 27 prime",
        .n = 27,
        .expected = 0,
    },
    {
        .desc = "Is 29 prime",
        .n = 29,
        .expected = 1,
    },
    {
        .desc = "Is 31 prime",
        .n = 31,
        .expected = 1,
    },
    {
        .desc = "Is 37 prime",
        .n = 37,
        .expected = 1,
    },
    {
        .desc = "Is 41 prime",
        .n = 41,
        .expected = 1,
    },
    {
        .desc = "Is 43 prime",
        .n = 43,
        .expected = 1,
    },
    {
        .desc = "Is 47 prime",
        .n = 47,
        .expected = 1,
    },
    {
        .desc = "Is 49 prime",
        .n = 49,
        .expected = 0,
    },
    {
        .desc = "Is 53 prime",
        .n = 53,
        .expected = 1,
    },
    {
        .desc = "Is 121 prime (11 * 11)",
        .n = 121,
        .expected = 0,
    },
    {
        .desc = "Is 127 prime",
        .n = 127,
        .expected = 1,
    },
    {
        .desc = "Is 169 prime (13 * 13)",
        .n = 169,
        .expected = 0,
    },
    {
        .desc = "Is 179 prime",
        .n = 179,
        .expected = 1,
    },
    {
        .desc = "Is 221 prime (13 * 17)",
        .n = 221,
        .expected = 0,
    },
    {
        .desc = "Is 223 prime",
        .n = 223,
        .expected = 1,
    },
    {
        .desc = "Is 293 prime",
        .n = 293,
        .expected = 1,
    },
    {
        .desc = "Is 323 prime (17 * 19)",
        .n = 323,
        .expected = 0,
    },
    {
        .desc = "Is 331 prime",
        .n = 331,
        .expected = 1,
    },
    {
        .desc = "Is 391 prime (17 * 23)",
        .n = 391,
        .expected = 0,
    },
    {
        .desc = "Is 409 prime",
        .n = 409,
        .expected = 1,
    },
    {
        .desc = "Is 437 prime (19 * 23)",
        .n = 437,
        .expected = 0,
    },
    {
        .desc = "Is 443 prime",
        .n = 443,
        .expected = 1,
    },
    {
        .desc = "Is 899 prime (29 * 31)",
        .n = 899,
        .expected = 0,
    },
    {
        .desc = "Is 907 prime",
        .n = 907,
        .expected = 1,
    },
    {
        .desc = "Is 2147483647 prime",
        .n = 2147483647,
        .expected = 1,
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
        int result = ft_is_prime(tests[i].n);

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
