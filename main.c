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
	int j;
	i = 0;
	char **map;
	char **six_lines;
	if (ac != 2)
		ft_error();
	check_extension(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("no file\n");
		return (close(fd), 1);
	}
	map = map_filling(fd);
	while(map[i])
		printf("%s\n",map[i++]);
	j = -1;
	six_lines = malloc(sizeof(char *) * 6 + 1);
	while(map[j++] && j < 6)
	{
		six_lines[j] = malloc(ft_strlen(map[j]) + 1);
		six_lines[j] = strdup(map[j]);
	}
	six_lines[j] = NULL;
	i = 0;
	j = 0;
	while(six_lines[i])
	{
		if(check_first_sixlines(six_lines[i++], &j))
		{
			printf("error\n");
			return (1);
		}
	}
	if(j != 6)
	{
		printf("error mising element\n");
		return(0);
	}
	if (check_duble_element(six_lines))
	{
		printf("error double element\n");
		return (1);
	}
	if (check_textur(six_lines))
	{
		printf("failed to load texture(s).\n");
		return (1);
	}
	if (check_colors(six_lines))
	{
		printf("missing colors\n");
		return (1);
	}
}