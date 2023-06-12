#include "../../../../ex02/ft_abs.h"
#include "../../../utils/constants.h"
#include <stdio.h>

typedef struct s_test
{
	char	*desc;
	int		input;
	int		expected;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Test 1: ABS with positive value",
			.input = 5,
			.expected = 5,
		},
		{
			.desc = "Test 2: ABS with negative value",
			.input = -5,
			.expected = 5,
		},
		{
			.desc = "Test 3: ABS with zero value",
			.input = 0,
			.expected = 0,
		},
	};
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
		result = ABS(tests[i].input);
		if (result != tests[i].expected)
		{
			printf("    " RED "[%d] %s Expected %d, got %d\n" DEFAULT, i + 1,
					tests[i].desc, tests[i].expected, result);
			error++;
		}
		else
		{
			printf("  " GREEN CHECKMARK GREY " [%d] %s Expected %d, got
					% d\n " DEFAULT, i + 1, tests[i].desc, result,
						tests[i]
							.expected);
		}
	}
	return (error);
}
