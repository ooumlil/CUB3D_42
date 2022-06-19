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
	// while(map[i])
	// 	printf("%s\n",map[i++]);
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
	i = 6;

	while(map[i])
	{
		printf("%s\n",map[i++]);
	}
	i = 6;
	// while(map[i])
	// {
	// 	j = 0;
	// 	while(map[i][j])
	// 	{
	// 		// if(map[i][j] == ' ' && map[i][j+1])
	// 		// 	while(map[i][j] == ' ')
	// 		// 		j++;
	// 		// if(map[i][j - 1] == ' ')
	// 		// 	if(map[i][j] != '1' || (map[i - 1][j] != '1' && i != 6 && map[i - 1][j] != '\0') || (map[i + 1][j] != '1' && map[i + 1]))
	// 		// 	{
	// 		// 		printf("P00\n");
	// 		// 		printf("%s\n",map[i]);
	// 		// 		return (0);
	// 		// 	}
	// 		if(map[i][j] == ' ')
	// 		{
	// 			while(map[i][j] == ' ')
	// 			{
	// 				if((map[i - 1][j] != '1' && i != 6) || map[i + 1][j] != '1' || map[i][j + 1] != '1')
	// 					printf("fy\n");
	// 				j++;
	// 			}
	// 			else
	// 			{
	// 				while(map[i][j] == ' ')
	// 				{
	// 					if((map[i - 1][j] != '1' && i != 6
	// 						&& map[i - 1][j] != '\0')
	// 						|| (map[i + 1][j] != '1' && map[i + 1][j] != '\0')|| ( map[i][j + 1] != '1'&& map[i][j +1] != '\0' )|| (map[i][j - 1] != '1' && map[i][j - 1] != '\0'))
	// 						printf("fb\n");
	// 					j++;
	// 				}
	// 			}
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	// ft_map_check(map);
	////////ali check map/////////
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (map[i][j - 1] != '1' && j != 0)
					printf("invalide map  1\n");
				while (map[i][j + 1] == ' ')
					j++;
				if (map[i][j + 1] != '1' && map[i][j+ 1])
					printf("invalide map  2\n");
			}
			j++;
		}
		i++;
	}
	j = 0;
	i = 6;
	while(map[i])
	{
		i = 6;
		while(map[i][j])
		{
			if (map[i][j] == ' ')
			{
				printf("ooook\n");
				if (map[i -1][j] != '1' && i != 6)
					printf("invalide map  3\n");
				while (map[i + 1][j] == ' ')
					i++;
				if (map[i + 1][j] != '1' && map[i + 1])
					printf("invalide map  4\n");
			}
			i++;
		}
		j++;
	}
}