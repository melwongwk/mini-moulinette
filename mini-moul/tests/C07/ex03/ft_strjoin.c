#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex03/ft_strjoin.c"
#include "../../../utils/constants.h"
#define LARGE_SIZE 1000
#define LONG_STRING "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"


typedef struct s_test
{
    char *desc;
    int size;
    char **strs;
    char *sep;
    char *expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    // Setup for large test
    char **large_strs = malloc(sizeof(char *) * LARGE_SIZE);
    char *large_expected = malloc(LARGE_SIZE + 1);
    for (int i = 0; i < LARGE_SIZE; i++)
    {
        large_strs[i] = "a";
        large_expected[i] = 'a';
    }
    large_expected[LARGE_SIZE] = '\0';

    t_test tests[] = {
        {
            .desc = "ft_strjoin with size 0",
            .size = 0,
            .strs = NULL,
            .sep = ",",
            .expected = ""
        },
        {
            .desc = "ft_strjoin with size 1",
            .size = 1,
            .strs = (char*[]){ "Hello" },
            .sep = ",",
            .expected = "Hello"
        },
        {
            .desc = "ft_strjoin with size 3",
            .size = 3,
            .strs = (char*[]){ "Hello", "world", "!" },
            .sep = ", ",
            .expected = "Hello, world, !"
        },
        {
            .desc = "ft_strjoin with size 4 and empty strings",
            .size = 4,
            .strs = (char*[]){ "", "Hello", "", "world" },
            .sep = "-",
            .expected = "-Hello--world"
        },
        {
            .desc = "ft_strjoin with size 2 and empty separator",
            .size = 2,
            .strs = (char*[]){ "Hello", "world" },
            .sep = "",
            .expected = "Helloworld"
        },
        {
            .desc = "ft_strjoin with all empty strings",
            .size = 3,
            .strs = (char*[]){ "", "", "" },
            .sep = ",",
            .expected = ",,"
        },
        {
            .desc = "ft_strjoin with special characters in separator",
            .size = 3,
            .strs = (char*[]){ "a", "b", "c" },
            .sep = "<->",
            .expected = "a<->b<->c"
        },
        {
            .desc = "ft_strjoin with 1000 repetitions of 'a'",
            .size = LARGE_SIZE,
            .strs = large_strs,
            .sep = "",
            .expected = large_expected
        },
        {
            .desc = "ft_strjoin with very long strings and separator",
            .size = 3,
            .strs = (char*[]){
                LONG_STRING,
                "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
                "cccccccccccccccccccccccccccccccccccccccccccccccccc"
            },
            .sep = "--SEPARATOR--",
            .expected = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa--SEPARATOR--bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb--SEPARATOR--cccccccccccccccccccccccccccccccccccccccccccccccccc"
        },
    };

    int count = sizeof(tests) / sizeof(tests[0]);
    int result = run_tests(tests, count);

    // Cleanup
    free(large_expected);
    free(large_strs);

    return result;
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        char *result = ft_strjoin(tests[i].size, tests[i].strs, tests[i].sep);

        if (strcmp(result, tests[i].expected) != 0)
        {
            printf("    " RED "[%d] %s Expected \"%s\", got \"%s\"\n", i + 1, tests[i].desc, tests[i].expected, result);
            error -= 1;
        }
        else
            printf("  " GREEN CHECKMARK GREY " [%d] %s Expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, tests[i].expected, result);

        free(result);
    }
    return error;
}