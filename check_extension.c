#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	check_extension(char *av)
{
	size_t	i;

	i = ft_strlen(av);
	if (av[i - 1] == 'b' && av[i - 2] == 'u' \
		&& av[i - 3] == 'c' && av[i - 4] == '.')
		return ;
	else
	{
		write (2, "Error\nWrong Extension!\n", 23);
		exit (1);
	}
}