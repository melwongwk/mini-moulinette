#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../ex05/ft_split.c"
#include "../../../utils/constants.h"

void print_words(char **words)
{
    if (!words)
    {
        printf("(null)");
        return;
    }
    printf("\"%s\"", words[0]);
    for (int i = 1; words[i]; i++)
        printf(", \"%s\"", words[i]);
}

typedef struct s_test
{
    char *desc;
    char *str;
    char *charset;
    char **expected;
} t_test;

int run_tests(t_test *tests, int count);

int main(void)
{
    t_test tests[] = {
        {
            .desc = "Empty string with empty charset",
            .str = "",
            .charset = "",
            .expected = (char *[]){ NULL },
        },
        {
            .desc = "Single-word string with empty charset",
            .str = "hello",
            .charset = "",
            .expected = (char *[]){ "hello", NULL },
        },
        {
            .desc = "String with leading and trailing separators",
            .str = ",,hello,world,,",
            .charset = ",",
            .expected = (char *[]){ "hello", "world", NULL },
        },
        {
            .desc = "String with multiple consecutive separators",
            .str = "hello,,,,world",
            .charset = ",",
            .expected = (char *[]){ "hello", "world", NULL },
        },
        {
            .desc = "String with repeated separators",
            .str = "aaabbbaaaccc",
            .charset = "ab",
            .expected = (char *[]){ "ccc", NULL },
        },
        // NEW TEST CASES
        {
            .desc = "Separators are all printable characters",
            .str = "a b\tc\nd",
            .charset = " \t\n",
            .expected = (char *[]){ "a", "b", "c", "d", NULL },
        },
        {
            .desc = "All characters are separators",
            .str = "abc",
            .charset = "abc",
            .expected = (char *[]){ NULL },
        },
        {
            .desc = "Separators in the middle only",
            .str = "word1|||word2",
            .charset = "|",
            .expected = (char *[]){ "word1", "word2", NULL },
        },
        {
            .desc = "Only one valid word surrounded by junk",
            .str = "###word###",
            .charset = "#",
            .expected = (char *[]){ "word", NULL },
        },
    };

    int count = sizeof(tests) / sizeof(tests[0]);

    return run_tests(tests, count);
}

int run_tests(t_test *tests, int count)
{
    int i;
    int error = 0;

    for (i = 0; i < count; i++)
    {
        char **result = ft_split(tests[i].str, tests[i].charset);

        if (!result && !tests[i].expected)
        {
            printf(GREEN CHECKMARK GREY " [%d] %s\n" DEFAULT, i + 1, tests[i].desc);
        }
        else if (!result || !tests[i].expected)
        {
            printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
            print_words(result);
            printf("\" instead of \"");
            print_words(tests[i].expected);
            printf("\"\n" DEFAULT);
            error -= 1;
        }
        else
        {
            int j = 0;
            while (tests[i].expected[j] && result[j])
            {
                if (strcmp(tests[i].expected[j], result[j]) != 0)
                {
                    printf(RED "[%d] %s Element %d: expected \"%s\", got \"%s\"\n" DEFAULT, i + 1, tests[i].desc, j, tests[i].expected[j], result[j]);
                    error -= 1;
                    break;
                }
                j++;
            }

            if (tests[i].expected[j] || result[j])
            {
                printf(RED "[%d] %s got \"", i + 1, tests[i].desc);
                print_words(result);
                printf("\" instead of \"");
                print_words(tests[i].expected);
                printf("\"\n" DEFAULT);
                error -= 1;
            }
            else
            {
                printf(GREEN CHECKMARK GREY " [%d] %s got \"", i + 1, tests[i].desc);
                print_words(result);
                printf("\" as expected\n" DEFAULT);
            }
        }

        if (result)
        {
            int j = 0;
            while (result[j])
            {
                free(result[j]);
                j++;
            }
            free(result);
        }
    }

    return (error);
}