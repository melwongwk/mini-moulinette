#include "../../../../ex04/ft_strs_to_tab.c"
#include "../../../utils/constants.h"
#include "resources/ft_stock_str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//void ft_show_tab(struct s_stock_str *par);

int	main(void)
{
	char				*strs[];
	int					size;
	struct s_stock_str	*result;

	strs[] = {"hello", "world", "this", "is", "a", "test"};
	size = sizeof(strs) / sizeof(char *);
	result = ft_strs_to_tab(size, strs);
	if (result == NULL)
	{
		printf("Error: ft_strs_to_tab returned NULL\n");
		return (1);
	}
	printf("  " GREEN CHECKMARK GREY " File was able to compile.\n" DEFAULT);
	//ft_show_tab(result);
	// Free the allocated memory
	for (int i = 0; i < size; i++)
	{
		free(result[i].copy);
	}
	free(result);
	return (0);
}
