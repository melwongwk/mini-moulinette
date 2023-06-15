#include "../../../../ex01/ft_boolean.h"
#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

t_bool	ft_is_even(int nbr)
{
	return ((EVEN(nbr)) ? TRUE : FALSE);
}

int	_main(int argc, char **argv)
{
	(void)argv;
	if (ft_is_even(argc - 1) == TRUE)
		ft_putstr(EVEN_MSG);
	else
		ft_putstr(ODD_MSG);
	return (SUCCESS);
}

typedef struct s_test
{
	char	*desc;
	char	**argv;
	char	*expected;
}			t_test;

int	get_argc(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

int	run_test(t_test test, int index)
{
	char	*buffer;
	int		saved_stdout;
	int		return_value;
	int		ret;

	saved_stdout = stdout_open();
	return_value = _main(get_argc(test.argv), test.argv);
	buffer = stdout_read();
	stdout_close(saved_stdout);
	ret = -1;
	if (return_value != 0)
		printf("    " RED "[%d] %s Expected return value \"%d\", got \"%d\"\n", index, test.desc, 0, return_value);
	else if (strcmp(test.expected, buffer) != 0)
		printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", index, test.desc, test.expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, index, test.desc, buffer);
		ret = 0;
	}
	free(buffer);
	return (ret);
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
	{.desc = "ft_print_program_name with no argument", .argv = (char *[]){"program_name", NULL}, .expected = "I have an even number of arguments.\n"},
	{.desc = "ft_print_program_name with one argument", .argv = (char *[]){"program_name", "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", NULL}, .expected = "I have an odd number of arguments.\n"},
	{.desc = "ft_print_program_name with two arguments", .argv = (char *[]){"program_name", "arg1", "arg2", NULL}, .expected = "I have an even number of arguments.\n"},
	};

	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}
