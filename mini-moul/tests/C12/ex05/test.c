#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_push_front(t_list **begin_list, void *data);
t_list *ft_list_push_strs(int size, char **strs);
t_list	*ft_list_last(t_list *begin_list);

// Test declarations
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);

int main(void) {
    int result = 0;

    if (test1() != 0) result = -1;
    if (test2() != 0) result = -1;
    if (test3() != 0) result = -1;
    if (test4() != 0) result = -1;
    if (test5() != 0) result = -1;
	if (test6() != 0) result = -1;

    return result;
}

// Tests

int test1(void) {
    char *strs[] = {"First", "Second", "Third"};
    t_list *list = ft_list_push_strs(3, strs);

    const char *expected[] = {"Third", "Second", "First"};
    int i = 0;
    t_list *tmp = list;

    while (tmp && i < 3) {
        if (strcmp((char *)tmp->data, expected[i]) != 0) {
            printf("    " RED "[1] Basic test failed\n" DEFAULT);
            while (list) {
                t_list *free_tmp = list;
                list = list->next;
                free(free_tmp);
            }
            return -1;
        }
        tmp = tmp->next;
        i++;
    }

    if (i != 3 || tmp != NULL) {
        printf("    " RED "[1] Basic test failed (wrong length)\n" DEFAULT);
        while (list) {
            t_list *free_tmp = list;
            list = list->next;
            free(free_tmp);
        }
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [1] Basic test passed\n" DEFAULT);
    while (list) {
        t_list *free_tmp = list;
        list = list->next;
        free(free_tmp);
    }
    return 0;
}

int test2(void) {
    char *strs[] = {"Single"};
    t_list *list = ft_list_push_strs(1, strs);
    
    if (!list || strcmp((char *)list->data, "Single") != 0 || list->next != NULL) {
        printf("    " RED "[2] Single string test failed\n" DEFAULT);
        free(list);
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [2] Single string test passed\n" DEFAULT);
    free(list);
    return 0;
}

int test3(void) {
    char *strs[] = {"A", "B", "C", "D", "E"};
    t_list *list = ft_list_push_strs(5, strs);

    const char *expected[] = {"E", "D", "C", "B", "A"};
    int i = 0;
    t_list *tmp = list;

    while (tmp && i < 5) {
        if (strcmp((char *)tmp->data, expected[i]) != 0) {
            printf("    " RED "[3] Multiple string test failed\n" DEFAULT);
            while (list) {
                t_list *free_tmp = list;
                list = list->next;
                free(free_tmp);
            }
            return -1;
        }
        tmp = tmp->next;
        i++;
    }

    if (i != 5 || tmp != NULL) {
        printf("    " RED "[3] Multiple string test failed (wrong length)\n" DEFAULT);
        while (list) {
            t_list *free_tmp = list;
            list = list->next;
            free(free_tmp);
        }
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [3] Multiple string test passed\n" DEFAULT);
    while (list) {
        t_list *free_tmp = list;
        list = list->next;
        free(free_tmp);
    }
    return 0;
}

int test4(void) {
    char *strs[] = {"First", "Middle", "Last"};
    t_list *list = ft_list_push_strs(3, strs);
    
    t_list *last = ft_list_last(list);
    if (!last || strcmp((char *)last->data, "First") != 0) {
        printf("    " RED "[4] Order test failed\n" DEFAULT);
        while (list) {
            t_list *tmp = list;
            list = list->next;
            free(tmp);
        }
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [4] Order test passed\n" DEFAULT);
    while (list) {
        t_list *tmp = list;
        list = list->next;
        free(tmp);
    }
    return 0;
}

int test5(void) {
    char *strs[] = {"", "First", "Second"};
    t_list *list = ft_list_push_strs(3, strs);

    const char *expected[] = {"Second", "First", ""};
    int i = 0;
    t_list *tmp = list;

    while (tmp && i < 3) {
        if (strcmp((char *)tmp->data, expected[i]) != 0) {
            printf("    " RED "[5] Empty string test failed\n" DEFAULT);
            while (list) {
                t_list *free_tmp = list;
                list = list->next;
                free(free_tmp);
            }
            return -1;
        }
        tmp = tmp->next;
        i++;
    }

    if (i != 3 || tmp != NULL) {
        printf("    " RED "[5] Empty string test failed (wrong length)\n" DEFAULT);
        while (list) {
            t_list *free_tmp = list;
            list = list->next;
            free(free_tmp);
        }
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [5] Empty string test passed\n" DEFAULT);
    while (list) {
        t_list *free_tmp = list;
        list = list->next;
        free(free_tmp);
    }
    return 0;
}

int test6(void) {
    t_list *list = ft_list_push_strs(0, NULL);

    if (list != NULL) {
        printf("    " RED "[6] Zero strings test failed\n" DEFAULT);
        // Free just in case
        while (list) {
            t_list *tmp = list;
            list = list->next;
            free(tmp);
        }
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [6] Zero strings test passed\n" DEFAULT);
    return 0;
}

t_list	*ft_create_elem(void *data)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->next = NULL;
	return (elem);
}

t_list	*ft_list_last(t_list *begin_list)
{
	t_list	*current;

	current = begin_list;
	while (current)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}
