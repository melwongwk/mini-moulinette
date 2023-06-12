#include "../../../../ex06/ft_str_is_printable.c"
#include "../../../utils/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*str;
	char	*msg;
	int		expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{.str = "ABDELKFSCO",
			.msg = "ABDELKFSCO",
			.expected = 1},
		{.str = "\n\t\v\f",
			.msg = "\\n\\t\\v\\f",
			.expected = 0},
		{.str = "-_134556efSghij67",
			.msg = "-_134556efSghij67",
			.expected = 1}};
	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int	i;
	int	error;
	int	result;

	error = 0;
	for (i = 0; i < count; i++)
	{
		result = ft_str_is_printable(tests[i].str);
		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] ft_str_is_printable(\"%s\") Expected %d, got
					% d\n " DEFAULT, i + 1, tests[i].msg, tests[i].expected,
					result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] ft_str_is_printable(\"%s\") Expected
						% d,
					got % d\n " DEFAULT, i + 1, tests[i].msg,
							tests[i]
								.expected,
					result);
	}
	return (error);
}
