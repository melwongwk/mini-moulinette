#include "../../../../ex08/ft_ten_queens_puzzle.c"
#include "../../../utils/constants.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	test1(void);

int	main(void)
{
	if (test1() != 0)
		return (-1);
	return (0);
}

int	test1(void)
{
	if (1 > 0)
	{
		printf("    " RED "[1] Sorry, test not implemented yet.\n" DEFAULT, );
		return (-1);
	}
	return (0);
}
