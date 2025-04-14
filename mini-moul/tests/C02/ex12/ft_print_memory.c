#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../../../ex12/ft_print_memory.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
	char *desc;
	void *addr;
	unsigned int size;
	int expected_lines;
	char **expected_output;
} t_test;

int compare_output(FILE *fp, char **expected, int expected_lines)
{
	char buffer[2048];
	int line_count = 0;

	while (fgets(buffer, sizeof(buffer), fp) != NULL && line_count < expected_lines)
	{
		// Remove trailing newline
		int len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';

		char *buffer_after_colon = strchr(buffer, ':');
		char *expected_after_colon = strchr(expected[line_count], ':');

		if (!buffer_after_colon || !expected_after_colon)
		{
			printf("    ❌ Line %d: Colon not found in either actual or expected\n", line_count);
			return 0;
		}

		char *actual = buffer_after_colon + 1;
		char *expect = expected_after_colon + 1;

		if (strcmp(actual, expect) != 0)
		{
			printf("    ❌ Line %d mismatch:\n", line_count + 1);
			printf("       Expected: [%s]\n", expect);
			printf("       Actual:   [%s]\n", actual);
			return 0;
		}

		line_count++;
	}

	if (line_count != expected_lines)
	{
		printf("    ❌ Output line count mismatch: got %d, expected %d\n", line_count, expected_lines);
		return 0;
	}

	return 1;
}

int run_tests(t_test *tests, int count) {
    int error = 0;
    for (int i = 0; i < count; i++) {
        fflush(stdout);
        int saved_stdout = dup(STDOUT_FILENO);
        int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        void *result = ft_print_memory(tests[i].addr, tests[i].size);

        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);

        if (result != tests[i].addr) {
            printf("    " RED "[%d] %s - Function did not return the original address\n" DEFAULT, i + 1, tests[i].desc);
            error--;
        }

        FILE *fp = fopen("output.txt", "r");
        int output_matches = compare_output(fp, tests[i].expected_output, tests[i].expected_lines);
        fclose(fp);

        if (!output_matches) {
            printf("    " RED "[%d] %s - Output does not match expected\n" DEFAULT, i + 1, tests[i].desc);
            error--;
        } else {
            printf("  " GREEN CHECKMARK GREY " [%d] %s passed\n" DEFAULT, i + 1, tests[i].desc);
        }

        remove("output.txt");
    }
    return error;
}

int main(void)
{
	char *str1 = "Bonjour les aminches\t\n\tc\a est fou\ttout\tce qu on peut faire avec\t\n\tprint_memory\n\n\n\tlol.lol\n ";
	char *expected1[] = {
		"0000000000000000: 426f 6e6a 6f75 7220 6c65 7320 616d 696e Bonjour les amin",
		"0000000000000010: 6368 6573 090a 0963 0720 6573 7420 666f ches...c. est fo",
		"0000000000000020: 7509 746f 7574 0963 6520 7175 206f 6e20 u.tout.ce qu on ",
		"0000000000000030: 7065 7574 2066 6169 7265 2061 7665 6309 peut faire avec.",
		"0000000000000040: 0a09 7072 696e 745f 6d65 6d6f 7279 0a0a ..print_memory..",
		"0000000000000050: 0a09 6c6f 6c2e 6c6f 6c0a 2000           ..lol.lol. ."
	};

	char *str2 = "";
	char *expected2[] = {
		"0000000000000000: 00                                      ."
	};
	
	char *str3 = "Hello";
	char *expected3[] = {
		"0000000000000000: 4865 6c6c 6f00                          Hello."
	};

	char *str4 = "0123456789ABCDEF";
	char *expected4[] = {
		"0000000000000000: 3031 3233 3435 3637 3839 4142 4344 4546 0123456789ABCDEF"
	};

	char str5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0};
	char *expected5[] = {
		"0000000000000000: 0102 0304 0506 0708 090a 0b0c 0d0e 0f10 ................"
	};

	char str6[] = {'A', 'B', 'C', 1, 2, 3, 4, 'D', 'E', 'F', 5, 6, 7, 8, 'G', 'H', 'I', 0};
	char *expected6[] = {
		"0000000000000000: 4142 4301 0203 0444 4546 0506 0708 4748 ABC....DEF....GH",
		"0000000000000010: 4900                                    I."
	};

	char *str7 = "This will not be displayed";
	char *expected7[] = { "" };

	t_test tests[] = {
		{"ft_print_memory - Standard example", str1, 92, 6, expected1},
		{"ft_print_memory - Empty string (null terminator only)", str2, 1, 1, expected2},
		{"ft_print_memory - Small string", str3, 6, 1, expected3},
		{"ft_print_memory - Exactly 16 bytes", str4, 16, 1, expected4},
		{"ft_print_memory - Non-printable characters", str5, 16, 1, expected5},
		{"ft_print_memory - Mix of printable and non-printable", str6, 18, 2, expected6},
		{"ft_print_memory - Zero size (should print nothing)", str7, 0, 0, expected7}
	};

	int count = sizeof(tests) / sizeof(tests[0]);
	return run_tests(tests, count);
}
