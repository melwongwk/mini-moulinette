#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_map.h"
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

void	print(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%d ", tab[i]);
		i++;
	}
}

int	func1(int nbr)
{
	printf("%d ", nbr);
	return (nbr * 2);
}

int	test1(void)
{
	int		len = 5;
	int		tab[] = {1, 2, 3, 4, 5};
	int		*tab_ret;
	char	expected_out[] = "1 2 3 4 5 ";
	char	expected_ret[] = "2 4 6 8 10 ";
	char	*buffer;
	char	*buffer_ret;
	int		saved_stdout;
	int		ret;

	saved_stdout = stdout_open();
	tab_ret = ft_map(tab, len, func1);
	buffer = stdout_read();
	stdout_close(saved_stdout);
	saved_stdout = stdout_open();
	print(tab_ret, len);
	buffer_ret = stdout_read();
	stdout_close(saved_stdout);
	free(tab_ret);
	ret = -1;
	if (strcmp(buffer, expected_out) != 0)
		printf("    " RED "[1] ft_map({1, 2, 3, 4, 5}, 5, print_and_double) Expected \"%s\", got \"%s\"\n" DEFAULT, buffer, expected_out);
	else if (strcmp(buffer_ret, expected_ret) != 0)
		printf("    " RED "[1] tab = ft_map({1, 2, 3, 4, 5}, 5, print_and_double) Expected tab=\"%s\", got tab=\"%s\"\n" DEFAULT, buffer_ret, expected_ret);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [1] tab=ft_map({1, 2, 3, 4, 5}, 5, print_and_double) output tab=\"%s\" as expected\n" DEFAULT, buffer_ret);
		ret = 0;
	}
	free(buffer);
	return (ret);
}
