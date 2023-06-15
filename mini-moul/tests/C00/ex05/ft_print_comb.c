#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_print_comb.h"
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
	const char	*expected_output = "012, 013, 014, 015, 016, 017, 018, 019, 023, 024, 025, 026, 027, 028, 029, 034, 035, 036, 037, 038, 039, 045, 046, 047, 048, 049, 056, 057, 058, 059, 067, 068, 069, 078, 079, 089, 123, 124, 125, 126, 127, 128, 129, 134, 135, 136, 137, 138, 139, 145, 146, 147, 148, 149, 156, 157, 158, 159, 167, 168, 169, 178, 179, 189, 234, 235, 236, 237, 238, 239, 245, 246, 247, 248, 249, 256, 257, 258, 259, 267, 268, 269, 278, 279, 289, 345, 346, 347, 348, 349, 356, 357, 358, 359, 367, 368, 369, 378, 379, 389, 456, 457, 458, 459, 467, 468, 469, 478, 479, 489, 567, 568, 569, 578, 579, 589, 678, 679, 689, 789";
	int			saved_stdout;
	char		buffer[1024];

	saved_stdout = stdout_open();
	ft_print_comb();
	stdout_close(saved_stdout, buffer, sizeof(buffer));
	if (strcmp(buffer, expected_output) != 0)
	{
		printf("    " RED "[1] ft_print_comb() Expected \"%s\", got \"%s\"\n" DEFAULT,
			expected_output,
			buffer);
		return (-1);
	}
	else
		printf("  " GREEN CHECKMARK GREY " [1] ft_print_comb() Expected \"%s\", got \"%s\"\n" DEFAULT,
			expected_output,
			buffer);
	return (0);
}
