#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_putchar.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_test
{
	char	*desc;
	char	c;
	char	*expected;
}			t_test;

int	run_test(t_test test, int index)
{
	char	buffer[1024];
	int		saved_stdout;

	saved_stdout = stdout_open();
	ft_putchar(test.c);
	stdout_close(saved_stdout, buffer, sizeof(buffer));
	if (strcmp(buffer, test.expected) != 0)
	{
		printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", index, test.desc, test.expected, buffer);
		return (-1);
	}
	printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, index, test.desc, buffer);
	return (0 * index);
}

int	run_tests(const t_test *tests, int count)
{
	int		i;
	int		error;

	error = 0;
	i = 0;
	while (i < count)
	{
		error += run_test(tests[i], i + 1);
		i++;
	}
	return (error);
}

int	main(void)
{
	int				count;
	const t_test	tests[] = {
	{.desc = "ft_putchar('c')", .c = 'c', .expected = "c"},
	{.desc = "ft_putchar('x')", .c = 'x', .expected = "x"},
	{.desc = "ft_putchar(' ')", .c = ' ', .expected = " "},
	{.desc = "ft_putchar('\\n')", .c = '\n', .expected = "\n"},
	{.desc = "ft_putchar('\\t')", .c = '\t', .expected = "\t"},
	{.desc = "ft_putchar('\\0')", .c = '\0', .expected = "\0"},
	{.desc = "ft_putchar('\\xFF')", .c = '\xFF', .expected = "\xFF"},
	};

	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}
