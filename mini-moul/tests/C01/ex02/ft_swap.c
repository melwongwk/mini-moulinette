#include "../../../../ex02/ft_swap.c"
#include "../../../utils/constants.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_test
{
	char	*desc;
	int		x;
	int		y;
	int		expected_x;
	int		expected_y;
}			t_test;

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{
			.desc = "Swap two positive integers",
			.x = 2,
			.y = 3,
			.expected_x = 3,
			.expected_y = 2,
		},
		{
			.desc = "Swap a positive and negative integer",
			.x = 9,
			.y = -4,
			.expected_x = -4,
			.expected_y = 9,
		},
		{
			.desc = "Swap two negative integers",
			.x = -32,
			.y = 54,
			.expected_x = 54,
			.expected_y = -32,
		},
		{
			.desc = "Swap numbers that may exceed INT_MAX if added",
			.x = 4576878,
			.y = 4576878,
			.expected_x = 4576878,
			.expected_y = 4576878,
		},
	};
	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
{
	int	i;
	int	error;
	int	x;
	int	y;

	error = 0;
	for (i = 0; i < count; i++)
	{
		x = tests[i].x;
		y = tests[i].y;
		ft_swap(&x, &y);
		if (x != tests[i].expected_x || y != tests[i].expected_y)
		{
			printf("    " RED "[%d] %s Expected x = %d, y = %d, got x = %d, y =
						% d\n " DEFAULT, i + 1, tests[i].desc,
							tests[i]
								.expected_x,
					tests[i]
						.expected_y,
					x,
					y);
			error--;
		}
		else
		{
			printf("  " GREEN CHECKMARK GREY " [%d] %s Passed\n" DEFAULT, i + 1,
					tests[i].desc);
		}
	}
	return (error);
}
