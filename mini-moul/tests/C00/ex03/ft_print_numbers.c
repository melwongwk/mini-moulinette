#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_print_numbers.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int	main(void)
{
	return (test1());
}

int	test1(void)
{
	int			saved_stdout;
	char		buffer[1024];
	const char	*expected_output = "0123456789";

	saved_stdout = stdout_open();
	ft_print_numbers();
	stdout_close(saved_stdout, buffer, sizeof(buffer));
	if (strcmp(buffer, expected_output) != 0)
	{
		printf("    " RED "[1] ft_print_numbers() Expected \"%s\", got \"%s\"\n" DEFAULT,
			expected_output,
			buffer);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_print_numbers() output \"%s\" as expected\n" DEFAULT,
			buffer);
	return (0);
}
