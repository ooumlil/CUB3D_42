/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/24 17:12:54 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	image_rendering(t_rend *game)
{
	game->i = 6;
	while(game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->i * game->height, game->j * game->width);
			game->j++;
		}
		game->i++;
	}
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

	puts("ff");
	game->mlx = mlx_init();
	int i;
	int k;
	i = 0;
	while(map[i])
	{
		if(ft_strlen(map[i]) > ft_strlen(map[i+1]))
			k = ft_strlen(map[i]);
		i++;
	}
	game->mlx_win = mlx_new_window(game->mlx, lines(map) * 30,k,  "cub3d");
	puts("gg");
	game->wall = mlx_xpm_file_to_image(game->mlx, "../assets/bluestone.xpm", &game->width, &game->height);
	game->map = map;
	puts("yy");
	image_rendering(game);
	puts("jj");
	mlx_loop(game->mlx);
}