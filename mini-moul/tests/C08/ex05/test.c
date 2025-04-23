#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_stock_str.h"
#include <stdio.h>
#include <stdlib.h>

void	free_stock_strs(t_stock_str *par)
{
	int	i = 0;

	while (par[i].str != NULL)
	{
		free(par[i].copy);
		i++;
	}
	free(par);
}

int	main(int argc, char **argv)
{
	t_stock_str	*par;

	par = ft_strs_to_tab(argc - 1, argv + 1);
	if (par == NULL)
		return (0);
	par[0].copy[0] += 32;
	ft_show_tab(par);
	free_stock_strs(par);
	return (0);
}
