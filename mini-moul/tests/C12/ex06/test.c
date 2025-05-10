#include "../../../utils/constants.h"
#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
t_list *ft_create_elem(void *data);
void ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
void free_data(void *data);

// Track free calls
int free_call_count = 0;

t_list *ft_create_elem(void *data) {
    t_list *elem = malloc(sizeof(t_list));
    if (!elem)
        return NULL;
    elem->data = data;
    elem->next = NULL;
    return elem;
}

void free_data(void *data) {
    free_call_count++;
    free(data);
}

// Test declarations
int test1(void);
int test2(void);
int test3(void);
int test4(void);
int test5(void);
int test6(void);
int test7(void);

int main(void) {
    int result = 0;

    if (test1() != 0) result = -1;
    if (test2() != 0) result = -1;
    if (test3() != 0) result = -1;
    if (test4() != 0) result = -1;
    if (test5() != 0) result = -1;
	if (test6() != 0) result = -1;
	if (test7() != 0) result = -1;

    return result;
}

int test1(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(strdup("Test"));
    ft_list_clear(list, free_data);

    if (free_call_count != 1) {
        printf("    " RED "[1] Basic test failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [1] Basic test passed\n" DEFAULT);
    return 0;
}

int test2(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(strdup("First"));
    list->next = ft_create_elem(strdup("Second"));
    list->next->next = ft_create_elem(strdup("Third"));

    ft_list_clear(list, free_data);

    if (free_call_count != 3) {
        printf("    " RED "[2] Multiple elements test failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [2] Multiple elements test passed\n" DEFAULT);
    return 0;
}

int test3(void) {
    free_call_count = 0;
    t_list *list = NULL;
    ft_list_clear(list, free_data);

    if (free_call_count != 0) {
        printf("    " RED "[3] Empty list test failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [3] Empty list test passed\n" DEFAULT);
    return 0;
}

int test4(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(NULL);
    ft_list_clear(list, free_data);

    if (free_call_count != 1) {
        printf("    " RED "[4] NULL data test failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [4] NULL data test passed\n" DEFAULT);
    return 0;
}

int test5(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(strdup("String1"));
    list->next = ft_create_elem(strdup("String2"));

    ft_list_clear(list, free_data);

    if (free_call_count != 2) {
        printf("    " RED "[5] Freeing dynamically allocated strings failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }
    printf("  " GREEN CHECKMARK GREY " [5] Freeing dynamically allocated strings passed\n" DEFAULT);
    return 0;
}

int test6(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(NULL);
    list->next = ft_create_elem(strdup("A"));
    list->next->next = ft_create_elem(NULL);
    list->next->next->next = ft_create_elem(strdup("B"));

    ft_list_clear(list, free_data);

    if (free_call_count != 4) {
        printf("    " RED "[6] Alternating NULL and valid data failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [6] Alternating NULL and valid data passed\n" DEFAULT);
    return 0;
}

int test7(void) {
    free_call_count = 0;
    t_list *list = ft_create_elem(NULL);
    list->next = ft_create_elem(NULL);
    list->next->next = ft_create_elem(NULL);

    ft_list_clear(list, free_data);

    if (free_call_count != 3) {
        printf("    " RED "[7] All NULL data test failed (free count: %d)\n" DEFAULT, free_call_count);
        return -1;
    }

    printf("  " GREEN CHECKMARK GREY " [7] All NULL data test passed\n" DEFAULT);
    return 0;
}
