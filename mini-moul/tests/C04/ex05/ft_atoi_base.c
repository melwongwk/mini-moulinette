#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_atoi_base.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *str;
    char *base;
    int expected_output;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Convert a binary number to decimal",
            .str = "101101",
            .base = "01",
            .expected_output = 45,
        },
        {
            .desc = "Convert a hexadecimal number to decimal",
            .str = "ff",
            .base = "0123456789abcdef",
            .expected_output = 255,
        },
        {
            .desc = "Convert a number with leading whitespace and sign to decimal",
            .str = "    +-14353",
            .base = "0123456789",
            .expected_output = -14353,
        },
        {
            .desc = "Convert a binary number with leading whitespace and sign to decimal",
            .str = "         ---10101001",
            .base = "01",
            .expected_output = -169,
        },
        {
            .desc = "Convert a hexadecimal number with leading space and sign to decimal",
            .str = "     +---59",
            .base = "0123456789abcdef",
            .expected_output = -89,
        },
        {
            .desc = "Convert a hexadecimal number with leading whitespace and sign to decimal",
            .str = " \t\v\f\n +---59",
            .base = "0123456789abcdef",
            .expected_output = -89,
        },
        {
            .desc = "Convert a hexadecimal number with smallest possible negative value",
            .str = "-80000000",
            .base = "0123456789abcdef",
            .expected_output = -2147483648,
        },
        {
            .desc = "Convert a hexadecimal number with leading whitespace and sign to decimal",
            .str = "7fffffff",
            .base = "0123456789abcdef",
            .expected_output = 2147483647,
        },
		{
			.desc = "Convert vfp in base 'poneyvif' to decimal",
            .str = "vfp",
            .base = "poneyvif",
            .expected_output = 376,
		},
		{
			.desc = "Invalid base(empty)",
            .str = "42",
            .base = "",
            .expected_output = 0,
		},
		{
			.desc = "Invalid base(1 char)",
            .str = "42",
            .base = "0",
            .expected_output = 0,
		},
		{
			.desc = "Invalid base(duplicate char)",
            .str = "42",
            .base = "01234567890",
            .expected_output = 0,
		},
		{
			.desc = "Invalid base(+ in base)",
            .str = "42",
            .base = "01234+56789",
            .expected_output = 0,
		},
		{
			.desc = "Invalid base(space in base)",
            .str = "42",
            .base = "01234 56789",
            .expected_output = 0,
		},
		{
			.desc = "Stops at invalid char",
            .str = "42a",
            .base = "0123456789",
            .expected_output = 42,
		},
		{
			.desc = "Just signs",
            .str = "----+++++",
            .base = "0123456789",
            .expected_output = 0,
		},
		{
			.desc = "Empty string",
            .str = "",
            .base = "0123456789",
            .expected_output = 0,
		},
        // Add more test cases here
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
        int result = ft_atoi_base(tests[i].str, tests[i].base);
        if (result != tests[i].expected_output)
        {
            printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected_output, result);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s output %d as expected\n" DEFAULT, i + 1, tests[i].desc, result);
    }

    return (error);
}
