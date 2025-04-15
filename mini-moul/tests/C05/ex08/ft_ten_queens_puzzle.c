#include "../../../utils/constants.h"
#include "ft_ten_queens_puzzle.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int	test1(void);

int	main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int	is_valid_solution_line(char *line)
{
	int	seen[10] = {0};
	int	i;

	for (i = 0; i < 10; i++)
	{
		if (line[i] < '0' || line[i] > '9')
			return (0); // Invalid character
		if (seen[line[i] - '0'])
			return (0); // Duplicate digit
		seen[line[i] - '0'] = 1;
	}
	return (line[10] == '\n'); // Must end with newline
}

int	test1(void)
{
	char	line[16]; // each line is 10 chars + '\n' + '\0'
	int		saved_stdout;
	int		output_fd;
	int		result;
	int		expected = 724;
	FILE	*fp;
	int		line_count = 0;

	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);

	result = ft_ten_queens_puzzle();

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);

	if (result != expected)
	{
		printf("    " RED "[1] Return value: Expected %d, got %d\n" DEFAULT,
				expected, result);
		remove("output.txt");
		return (-1);
	}

	fp = fopen("output.txt", "r");
	if (!fp)
	{
		printf("    " RED "[1] Failed to open output file\n" DEFAULT);
		return (-1);
	}

	while (fgets(line, sizeof(line), fp))
	{
		if (!is_valid_solution_line(line))
		{
			printf("    " RED "[1] Invalid line format: %s" DEFAULT, line);
			fclose(fp);
			remove("output.txt");
			return (-1);
		}
		line_count++;
	}
	fclose(fp);
	remove("output.txt");

	if (line_count != expected)
	{
		printf("    " RED "[1] Expected %d lines, got %d\n" DEFAULT,
				expected, line_count);
		return (-1);
	}

	printf("  " GREEN CHECKMARK GREY
			" [1] ft_ten_queens_puzzle() Output format and count OK\n" DEFAULT);
	return (0);
}