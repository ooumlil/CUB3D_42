/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/25 19:20:02 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	image_rendering(t_rend *game)
{
	game->i = 6;
	while(game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == ' ')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->spaces, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == game->player)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->j*10, game->i*10);
			game->j++;
		}
		game->i++;
	}
	return (0);
}

int	lines(char **map)
{
	int	i;

	i = 6;
	while (map[i])
		i++;
	return (i);
}

void	mlx_start(char **map,t_rend *game)
{
	// t_rend	game;

	int i;
	int k;
	i = 6;
	while(map[i] && map[i + 1])
	{
		if(ft_strlen(map[i]) > ft_strlen(map[i+1]))
			k = ft_strlen(map[i]);
		i++;
	}
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx,k*35,lines(map)*35,"cub3d");
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/p5.xpm", &game->width, &game->height);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, 0, 0);
	game->map = map;
	// puts("yy");
	image_rendering(game);
	// puts("jj");
	mlx_hook(game->mlx_win, 2, 0, &take_key, game);
	//mlx_hook(data.mlx_win, 17, 0, &ft_exit, &data);
	mlx_loop_hook(game->mlx, image_rendering, game);
	mlx_loop(game->mlx);
}