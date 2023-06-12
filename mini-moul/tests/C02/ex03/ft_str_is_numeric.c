#include "../../../../ex03/ft_str_is_numeric.c"
#include "../../../utils/constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*str;
	int		expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{.str = "01948987493",
			.expected = 1},
		{.str = "0484882j8995489",
			.expected = 0},
		{.str = "-_jsdsdc67sdlkc,",
			.expected = 0}};
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
		result = ft_str_is_numeric(tests[i].str);
		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] ft_str_is_numeric(\"%s\") Expected %d, got
					% d\n " DEFAULT, i + 1, tests[i].str, tests[i].expected,
					result);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY " [%d] ft_str_is_numeric(\"%s\") Expected
						% d,
					got % d\n " DEFAULT, i + 1, tests[i].str,
							tests[i]
								.expected,
					result);
	}
	return (error);
}
