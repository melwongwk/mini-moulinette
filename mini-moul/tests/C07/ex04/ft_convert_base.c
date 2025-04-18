#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex04/ft_convert_base.c"
#include "../../../../ex04/ft_convert_base2.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    char *nbr;
    char *base_from;
    char *base_to;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Convert positive decimal to binary",
            .nbr = "42",
            .base_from = "0123456789",
            .base_to = "01",
            .expected = "101010",
        },
        {
            .desc = "Convert negative decimal to binary",
            .nbr = "-42",
            .base_from = "0123456789",
            .base_to = "01",
            .expected = "-101010",
        },
        {
            .desc = "Convert binary to hexadecimal",
            .nbr = "101010",
            .base_from = "01",
            .base_to = "0123456789ABCDEF",
            .expected = "2A",
        },
        {
            .desc = "Convert positive zero",
            .nbr = "0",
            .base_from = "01",
            .base_to = "0123456789ABCDEF",
            .expected = "0",
        },
        {
            .desc = "Convert negative zero",
            .nbr = "-0",
            .base_from = "01",
            .base_to = "0123456789ABCDEF",
            .expected = "0",
        },
        {
            .desc = "Invalid base_from (0123456789 )",
            .nbr = "42",
            .base_from = "012345678 ",
            .base_to = "01",
            .expected = NULL,
        },
        {
            .desc = "Invalid base_to (01 )",
            .nbr = "42",
            .base_from = "0123456789",
            .base_to = "01 ",
            .expected = NULL,
        },
        {
            .desc = "Invalid base_to (011)",
            .nbr = "42",
            .base_from = "01234567899",
            .base_to = "011",
            .expected = NULL,
        },
		{
			.desc = "Multiple minus signs",
			.nbr = "--42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Mixed signs",
			.nbr = "-+42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "-101010",
		},
		{
			.desc = "Invalid character in input string (stops parsing at invalid char)",
			.nbr = "42Z",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Leading whitespace in input",
			.nbr = "   \t\n\r\v\f42",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "101010",
		},
		{
			.desc = "Convert INT_MIN from decimal to binary",
			.nbr = "-2147483648",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "-10000000000000000000000000000000",
		},
		{
			.desc = "Convert INT_MAX from decimal to binary",
			.nbr = "2147483647",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "1111111111111111111111111111111",
		},
		{
			.desc = "Convert INT_MIN from decimal to base36",
			.nbr = "-2147483648",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			.expected = "-ZIK0ZK",
		},
		{
			.desc = "Convert INT_MAX from decimal to base36",
			.nbr = "2147483647",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			.expected = "ZIK0ZJ",
		},
		{
			.desc = "Single-character base_from (invalid)",
			.nbr = "42",
			.base_from = "z",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Base with '+' character (invalid)",
			.nbr = "42",
			.base_from = "01234+6789",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Base with duplicate characters (invalid)",
			.nbr = "42",
			.base_from = "01234456789",
			.base_to = "01",
			.expected = NULL,
		},
		{
			.desc = "Valid base_from and base_to but invalid characters in nbr",
			.nbr = "123abc",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "1111011", // Should stop parsing at 'a'
		},
		{
			.desc = "Leading plus sign (positive number)",
			.nbr = "+42",
			.base_from = "0123456789",
			.base_to = "0123456789ABCDEF",
			.expected = "2A",
		},
		{
			.desc = "Only whitespace in input",
			.nbr = " \t\n",
			.base_from = "0123456789",
			.base_to = "01",
			.expected = "0", // nothing parsed = 0
		},
		{
			.desc = "Valid conversion from base 16 to base 10",
			.nbr = "FF",
			.base_from = "0123456789ABCDEF",
			.base_to = "0123456789",
			.expected = "255",
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
        char *result = ft_convert_base(tests[i].nbr, tests[i].base_from, tests[i].base_to);

        if (!result && !tests[i].expected)
        {
            printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (!result || !tests[i].expected)
        {
            printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1, tests[i].desc, result, tests[i].expected);
            error -= 1;
        }
        else if (strcmp(result, tests[i].expected) != 0)
        {
            printf(RED "[%d] %s got \"%s\" instead of \"%s\"\n" DEFAULT, i + 1, tests[i].desc, result, tests[i].expected);
            error -= 1;
        }
        else
        {
            printf(GREEN CHECKMARK GREY " [%d] %s got \"%s\" as expected\n" DEFAULT, i + 1, tests[i].desc, result);
        }

        free(result);
    }

    return error;
}
