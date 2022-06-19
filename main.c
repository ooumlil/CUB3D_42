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
	if(!map)
		return (1);
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
		if(check_first_sixlines(six_lines[i++]))
		{
			printf("error\n");
			return (1);
		}
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
	i = 6;
	int k;
	k = 0;
	while(map[k])
		k++;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[6][j] != '1' && map[6][j] != ' ' && i == 6)
			{ 
				printf("error int first line in map\n");
				return(0);
			}
			if(map[k - 1][j] != '1' && map[k - 1][j] != ' ' && i == k - 1)
			{ 
				printf("error int last line in map\n");
				return(0);
			}
			if(map[i][j] == '0' && i != 6 && i != k - 1)
			{
				if(map[i][j + 1] != '1' && map[i][j + 1] != '0' && map[i][j + 1] != 'E' && map[i][j + 1] != 'S' && map[i][j + 1] != 'W')
					printf("invalid asahbii 1\n");
				if(map[i][j - 1] != '1' && map[i][j - 1] != '0'&& map[i][j - 1] != 'E' && map[i][j - 1] != 'S' && map[i][j - 1] != 'W')
					printf("invalid asahbii 2 \n");
				if(map[i + 1][j] != '1' && map[i + 1][j] != '0'  && map[i + 1][j] != 'E' && map[i + 1][j] != 'S' && map[i + 1][j] != 'W')
					printf("invalid asahbii 3\n");
				if(map[i - 1][j] != '1' && map[i - 1][j] != '0'  && map[i - 1][j] != 'E' && map[i - 1][j] != 'S' && map[i - 1][j] != 'W')
					printf("invalid asahbii 4\n");
			}
			j++;
		}
		i++;
	}
}