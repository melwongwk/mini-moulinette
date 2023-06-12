#include "../../../utils/constants.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FUNCTION_COUNT 5

typedef struct
{
	char	*name;
	bool	exists;
}			function_check;

int	main(void)
{
	char	buffer[128];
	FILE	*header_file;

	function_check functions[FUNCTION_COUNT] = {
		{"ft_putchar", false},
		{"ft_swap", false},
		{"ft_putstr", false},
		{"ft_strlen", false},
		{"ft_strcmp", false},
	};
	header_file = popen("cat ../ex00/ft.h", "r");
	while (fgets(buffer, sizeof(buffer), header_file))
	{
		for (int i = 0; i < FUNCTION_COUNT; i++)
		{
			if (strstr(buffer, functions[i].name) != NULL)
			{
				functions[i].exists = true;
			}
		}
	}
	pclose(header_file);
	for (int i = 0; i < FUNCTION_COUNT; i++)
	{
		printf("%s %s\n", functions[i].name,
				functions[i].exists ? "exists" : "does not exist");
	}
	return (0);
}
