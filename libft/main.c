#include "libft.h"
#include <stdio.h>

int	main(void)
{
	printf("hello: %zu (expected 5)\n", ft_strlen("hello"));
	printf("Empty string: %zu (expected 0)\n", ft_strlen(""));
	printf("A: %zu (expected 1)\n", ft_strlen("A"));
	printf("hello world: %zu (expected 11)\n", ft_strlen("hello world"));
	return (0);
}
