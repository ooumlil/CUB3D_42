#include "cub3d.h"

void	ft_error(void)
{
	printf("Error\n2 Arguments Needed\n");
	exit (1);
}

int map_final_check(char **map)
{
	int		j;
	char	**six_lines;

	if (!map)
		return (1);
	j = -1;
	six_lines = malloc(sizeof(char *) * 6 + 1);
	while (map[j++] && j < 6)
		six_lines[j] = strdup(map[j]);
	six_lines[j] = NULL;
	if (map_parsing(six_lines, map))
		return(1);
	return(0);
}

int	main(int ac , char **av)
{
	int		fd;
	char	**map;

	if (ac != 2)
		ft_error();
	check_extension(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("File not Found\n"), close(fd), 1);
	map = map_filling(fd);
	if (!map_final_check(map))
		puts("let start mlx");
}
