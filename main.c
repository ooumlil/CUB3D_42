/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:56:28 by ooumlil           #+#    #+#             */
/*   Updated: 2022/06/24 22:13:45 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_exit()
{
	exit(0);
	//return(1);
}
void	ft_error(void)
{
	printf("Error\n2 Arguments Needed\n");
	exit (1);
}

int	main(int ac, char **av)
{
	int		fd;
	char	**map;
	t_rend  game;
	if (ac != 2)
		ft_error();
	check_extension(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("File not Found\n"), close(fd), 1);
	map = map_filling(fd);
	if (!map_final_check(map,&game))
	{
		mlx_start(map,&game);
	}
	return (0);
}
