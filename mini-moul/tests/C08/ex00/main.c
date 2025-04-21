#include "ft.h"
#include <stdio.h>

int main(void)
{
	char c = 'Z';
	int a = 1;
	int b = 2;
	char str[] = "Hello, 42!";

	// ft_putchar
	ft_putchar(c);
	ft_putchar('\n');

	// ft_putstr
	ft_putstr(str);
	ft_putchar('\n');

	// ft_strlen
	printf("Length: %d\n", ft_strlen(str));

	// ft_strcmp
	printf("Cmp1: %d\n", ft_strcmp("abc", "abc"));  // should be 0
	printf("Cmp2: %d\n", ft_strcmp("abc", "abd"));  // should be < 0
	printf("Cmp3: %d\n", ft_strcmp("abd", "abc"));  // should be > 0

	// ft_swap
	ft_swap(&a, &b);
	printf("Swapped: a=%d b=%d\n", a, b);

	return 0;
}
