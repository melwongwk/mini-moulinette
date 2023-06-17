#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_stock_str.h"
#include <stdio.h>


int	main(int argc, char **argv)
{
	t_stock_str	*par;

	par = ft_strs_to_tab(argc - 1, argv + 1);
	if (par == NULL)
		return (0);
	par[0].copy[0] += 32;
	ft_show_tab(par);
	return (0);
}
