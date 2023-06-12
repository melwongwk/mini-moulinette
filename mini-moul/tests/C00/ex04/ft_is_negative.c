#include "../../../utils/constants.h"
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

int			run_tests(t_test *tests, int count);

int	main(void)
{
	int	count;

	t_test tests[] = {
		{.desc = "ft_is_negative(8)", .n = 8, .expected = "P"},
		{.desc = "ft_is_negative(-115)", .n = -115, .expected = "N"},
		{.desc = "ft_is_negative(-2147483648)", .n = -2147483648,
			.expected = "N"},
		{.desc = "ft_is_negative(0)", .n = 0, .expected = "P"},
		{.desc = "ft_is_negative(2147483647)", .n = 2147483647, .expected = "P"}
		// Add more test cases here
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
		output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
		// Call the function to be tested
		ft_is_negative(tests[i].n);
		// Restore the original output
		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
		// Open the output file and check its contents
		fp = fopen("output.txt", "r");
		fgets(buffer, sizeof(buffer), fp);
		fclose(fp);
		// Check that the output matches the expected value
		if (strncmp(buffer, tests[i].expected, 1) != 0)
		{
			printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1,
					tests[i].desc, tests[i].expected, buffer);
			error -= 1;
		}
		else
			printf(
				"  " GREEN CHECKMARK GREY
				" [%d] %s output \"%s\" as expected\n" DEFAULT,
				i + 1,
				tests[i].desc,
				buffer);
		// Delete the output file
		remove("output.txt");
	}
	return (error);
}
