#include "../../../utils/constants.h"
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

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
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

int	run_tests(t_test *tests, int count)
{
	int		i;
	int		error;
	char	buffer[1024];
	int		saved_stdout;
	int		output_fd;
	FILE	*fp;

	error = 0;
	for (i = 0; i < count; i++)
	{
		// Flush the standard output buffer
		fflush(stdout);
		// Clear the buffer used to capture the output of the function being tested
		memset(buffer, 0, sizeof(buffer));
		// Redirect the output to a file
		saved_stdout = dup(STDOUT_FILENO);
		output_fd = open(
			"output.txt",
			O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		// Call the function to be tested
		ft_putchar(tests[i].c);
		// Restore the original output
		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		// Open the output file and check its contents
		fp = fopen("output.txt", "r");
		fgets(buffer, sizeof(buffer), fp);
		fclose(fp);
		// Check that the output matches the expected value
		if (strcmp(buffer, tests[i].expected) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1,
					tests[i].desc, tests[i].expected, buffer);
			error -= 1;
		}
		else
			printf("  " GREEN CHECKMARK GREY
					" [%d] %s output \"%s\" as expected\n" DEFAULT,
					i + 1,
					tests[i].desc,
					buffer);
		// Delete the output file
		remove("output.txt");
	}
	return (error);
}
