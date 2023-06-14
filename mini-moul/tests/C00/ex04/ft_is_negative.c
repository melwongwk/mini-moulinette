#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_is_negative.h"
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
}			t_test;

int	main(void)
{
	int				count;
	const t_test	tests[] = {
	{.desc = "ft_is_negative(8)", .n = 8, .expected = "P"},
	{.desc = "ft_is_negative(-115)", .n = -115, .expected = "N"},
	{.desc = "ft_is_negative(-2147483648)", .n = -2147483648, .expected = "N"},
	{.desc = "ft_is_negative(0)", .n = 0, .expected = "P"},
	{.desc = "ft_is_negative(2147483647)", .n = 2147483647, .expected = "P"}
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
	ft_is_negative(test.n);
	stdout_close(saved_stdout, buffer, sizeof(buffer));
	if (strncmp(buffer, test.expected, 1) != 0)
	{
		printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", index, test.desc, test.expected, buffer);
		return (-1);
	}
	printf(
		"  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, index, test.desc, buffer);
	return (0);
}
