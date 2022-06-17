#include "cub3d.h"

void	ft_error(void)
{
	printf("Error\n2 Arguments Needed\n");
	exit (1);
}

int	main(int ac , char **av)
{
	int		fd;
	int i;
	i = 0;
	char **map;
	if (ac != 2)
		ft_error();
	check_extension(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), 1);
	map = map_filling(fd);
	while(map[i])
		printf("%s\n",map[i++]);
	
}