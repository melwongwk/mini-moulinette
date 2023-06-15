#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_putnbr.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_test
{
	char	*desc;
	int		n;
	char	*expected;
}	t_test;

int	main(void)
{
	int				count;
	const t_test	tests[] = {
	{.desc = "ft_putnbr(0)", .n = 0, .expected = "0"},
	{.desc = "ft_putnbr(-2147483648)", .n = -2147483648, .expected = "-2147483648"},
	{.desc = "ft_putnbr(2147483647)", .n = 2147483647, .expected = "2147483647"},
	{.desc = "ft_putnbr(42)", .n = 42, .expected = "42"},
	{.desc = "ft_putnbr(-42)", .n = -42, .expected = "-42"},
	};

	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}

int	run_tests(t_test *tests, int count)
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

int	run_test(t_test test, int index)
{
	char	buffer[1024];
	int		saved_stdout;

	saved_stdout = stdout_open();
	ft_putnbr(test.n);
	stdout_close(saved_stdout, buffer, sizeof(buffer));
	if (strcmp(buffer, test.expected) != 0)
	{
		printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", index, test.desc, test.expected, buffer);
		return (-1);
	}
	printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, index, test.desc, buffer);
	return (0);
}
