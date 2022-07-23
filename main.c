/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:56:28 by ooumlil           #+#    #+#             */
/*   Updated: 2022/07/23 06:13:47 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//int rays[];
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
void player_init(t_rend *m)
{
	m->pplayer = malloc(sizeof(t_player));
	m->pplayer->x = 0;
	m->pplayer->y = 0;
	get_index(m,&m->pplayer->x,&m->pplayer->y);
	m->pplayer->turn_d = 0;
	m->pplayer->wlk_d = 0;
	if(m->player == 'N')
	{
		m->pplayer->rotatangle = 3*PI/2;
	}
	if(m->player == 'S')
			m->pplayer->rotatangle = PI/2;
	if(m->player == 'W')
		m->pplayer->rotatangle = PI;
	if(m->player == 'E')
			m->pplayer->rotatangle = 0;
	m->pplayer->moveSpeed = 1.5;
	m->pplayer->rotationSpeed = 3 * (PI/180);
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
		// game.mlx = mlx_init();
		//game.mlx_win = mlx_new_window(game.mlx,1080,700,"cub");
		//player_init(&game);
		//game.d = 10;
		//game.roa = PI/2;
		game.rays = malloc(sizeof(t_ray) * NUM_RAYS);
		mlx_start(map,&game);
		//mlx_loop(mlx);
		
	}
	return (0);
}
