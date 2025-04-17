#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../../../../ex01/ft_range.c"
#include "../../../utils/constants.h"

typedef struct s_test
{
    char *desc;
    int min;
    int max;
    int *expected;
} t_test;

void print_array(const int *arr, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%d", arr[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("]");
}

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {.desc = "ft_range with min 0, max 0",
         .min = 0,
         .max = 0,
         .expected = NULL},
        {.desc = "ft_range with min 0, max 5",
         .min = 0,
         .max = 5,
         .expected = (int[]){0, 1, 2, 3, 4}},
        {.desc = "ft_range with min -5, max 5",
         .min = -5,
         .max = 5,
         .expected = (int[]){-5, -4, -3, -2, -1, 0, 1, 2, 3, 4}},
        {.desc = "ft_range with min -10, max -5",
         .min = -10,
         .max = -5,
         .expected = (int[]){-10, -9, -8, -7, -6}},
        {.desc = "ft_range with min 5, max 0",
         .min = 5,
         .max = 0,
         .expected = NULL},
        {.desc = "ft_range with min 42, max 43",
         .min = 42,
         .max = 43,
         .expected = (int[]){42}},
        {.desc = "ft_range with min 1000, max 1010",
         .min = 1000,
         .max = 1010,
         .expected = (int[]){1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009}},
        {.desc = "ft_range with INT_MIN, INT_MIN+3",
         .min = INT_MIN,
         .max = INT_MIN + 3,
         .expected = (int[]){INT_MIN, INT_MIN + 1, INT_MIN + 2}},
    };

    int count = sizeof(tests) / sizeof(tests[0]);
    return (run_tests(tests, count));
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        int *result = ft_range(tests[i].min, tests[i].max);
        int expected_size = (tests[i].expected == NULL) ? 0 : (tests[i].max - tests[i].min);

        if (tests[i].min >= tests[i].max || tests[i].expected == NULL)
        {
            if (result != NULL)
            {
                printf("    " RED "[%d] %s\n      Expected: NULL, Got: %p\n" DEFAULT,
                       i + 1, tests[i].desc, result);
                error -= 1;
            }
            else
            {
                printf("  " GREEN CHECKMARK GREY " [%d] %s\n      Expected: NULL, Got: NULL\n" DEFAULT,
                       i + 1, tests[i].desc);
            }
        }
        else
        {
            if (result == NULL)
            {
                printf("    " RED "[%d] %s\n      Expected: array, Got: NULL\n" DEFAULT,
                       i + 1, tests[i].desc);
                error -= 1;
            }
            else if (memcmp(result, tests[i].expected, expected_size * sizeof(int)) != 0)
            {
                printf("    " RED "[%d] %s\n" DEFAULT, i + 1, tests[i].desc);
                printf("      Expected: ");
                print_array(tests[i].expected, expected_size);
                printf("\n      Got     : ");
                print_array(result, expected_size);
                printf("\n");
                error -= 1;
            }
            else
            {
                printf("  " GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
            }
        }

        free(result);
    }

    return error;
}
