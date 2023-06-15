#include "../../../utils/constants.h"
#include "../../../utils/stdout_proxy.h"
#include "ft_print_combn.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_test
{
	char	*desc;
	int		n;
	char	*expected;
}	t_test;

int	run_test(const t_test test, int index)
{
	char		*buffer;
	int			saved_stdout;
	int			ret;

	saved_stdout = stdout_open();
	ft_print_combn(test.n);
	buffer = stdout_read();
	stdout_close(saved_stdout);
	ret = -1;
	if (strcmp(buffer, test.expected) != 0)
		printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", index, test.desc, test.expected, buffer);
	else
	{
		printf("  " GREEN CHECKMARK GREY " [%d] %s output \"%s\" as expected\n" DEFAULT, index, test.desc, buffer);
		ret = 0;
	}
	free(buffer);
	return (ret);
}

int	run_tests(const t_test *tests, int count)
{
	int		i;
	int		error;

	error = 0;
	i = 0;
	while (i < count)
	{
		error += run_test(tests[i], i + 1);
		i++;
	}
	return (error);
}

int	main(void)
{
	int				count;
	const t_test	tests[] = {
	{.desc = "ft_print_combn(2)", .n = 2, .expected = "01, 02, 03, 04, 05, 06, 07, 08, 09, 12, 13, 14, 15, 16, 17, 18, 19, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36, 37, 38, 39, 45, 46, 47, 48, 49, 56, 57, 58, 59, 67, 68, 69, 78, 79, 89"},
	{.desc = "ft_print_combn(3)", .n = 3, .expected = "012, 013, 014, 015, 016, 017, 018, 019, 023, 024, 025, 026, 027, 028, 029, 034, 035, 036, 037, 038, 039, 045, 046, 047, 048, 049, 056, 057, 058, 059, 067, 068, 069, 078, 079, 089, 123, 124, 125, 126, 127, 128, 129, 134, 135, 136, 137, 138, 139, 145, 146, 147, 148, 149, 156, 157, 158, 159, 167, 168, 169, 178, 179, 189, 234, 235, 236, 237, 238, 239, 245, 246, 247, 248, 249, 256, 257, 258, 259, 267, 268, 269, 278, 279, 289, 345, 346, 347, 348, 349, 356, 357, 358, 359, 367, 368, 369, 378, 379, 389, 456, 457, 458, 459, 467, 468, 469, 478, 479, 489, 567, 568, 569, 578, 579, 589, 678, 679, 689, 789"},
	{.desc = "ft_print_combn(9)", .n = 9, .expected = "012345678, 012345679, 012345689, 012345789, 012346789, 012356789, 012456789, 013456789, 023456789, 123456789"},
	};

	count = sizeof(tests) / sizeof(tests[0]);
	return (run_tests(tests, count));
}
