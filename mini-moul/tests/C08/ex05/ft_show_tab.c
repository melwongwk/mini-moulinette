#include "../../../../ex05/ft_show_tab.c"
#include "../../../utils/constants.h"
#include "resources/ft_stock_str.h"
#include "resources/ft_strs_to_tab.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	ft_show_tab(ft_strs_to_tab(argc, argv));
	printf("  " GREEN CHECKMARK GREY " File was able to compile.\n" DEFAULT);
}
