#include "cub3d.h"

int	num_of_lines(char **av)
{
	int		fd;
	int		i;
	char	*tmp;

	i = 0;
	fd = open(av[1], O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		free (tmp);
		if (!tmp)
			break ;
		i++;
	}
	return (close(fd), i);
}

char	**map_filling(char **av)
{
	int		num;
	char	**map;

	num = num_of_lines(av);
	map = (char **)malloc(sizeof(char *) * num + 1);
	if (!map)
		return (NULL);
}