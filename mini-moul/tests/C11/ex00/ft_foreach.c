#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_foreach.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int	test1(void);

int	main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

void	func1(int nbr)
{
	printf("%d ", nbr);
}

int	test1(void)
{
	int		tab[] = {1, 2, 3, 4, 5};
	char	expected[] = "1 2 3 4 5 ";
	char	*buffer;
	int		saved_stdout;
	int		ret;

	saved_stdout = stdout_open();
	ft_foreach(tab, sizeof(tab) / sizeof(tab[0]), func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);
	ret = -1;
	if (strcmp(buffer, expected) != 0)
		printf("    " RED "[1] ft_foreach({1, 2, 3, 4, 5}, 5, print) Expected \"%s\", got \"%s\"\n" DEFAULT, buffer, expected);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [1] ft_foreach({1, 2, 3, 4, 5}, 5, print) output \"%s\" as expected\n" DEFAULT, buffer);
		ret = 0;
	}
	free(buffer);
	return (ret);
}
