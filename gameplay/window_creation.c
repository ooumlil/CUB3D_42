/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/27 22:53:25 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void drawDDA(int xA,int yA,int xB,int yB,t_rend *game)
{
	int dx = xB - xA;
	int dy = yB - yA;

	float step = fmaxf(abs(dx),abs(dy));
	float xinc = dx/step;
	float yinc = dy/step;

	float x = xA,y = yA;

	while (step >= 0)
	{
		mlx_pixel_put(game->mlx,game->mlx_win,round(x),round(y),0xff3300);
		x += xinc;
		y += yinc;	
		step--;
	}
	
	
	
}
int	image_rendering(t_rend *game)
{
	game->i = 0;
	while(game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if(game->map[game->i][game->j] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*5, game->i*5);
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->black, game->j*5, game->i*5);
			if(game->map[game->i][game->j] == game->player)
			{
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*5, game->i*5);
				// mlx_pixel_put (game->mlx,game->mlx_win,game->j+cos(pi/2)*10,game->i+sin(pi/2)*10, 0xFF00);
				// mlx_pixel_put (game->mlx,game->mlx_win,game->j*50,game->i*50,0xff3300);
			}
			game->j++;
		}
		game->i++;
	}
	game->i = 0;
	while(game->map[game->i])
	{
		game->j = 0;
		while(game->map[game->i][game->j])
		{
			if(game->map[game->i][game->j] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*5, game->i*5);
			if(game->map[game->i][game->j] == game->player)
			{
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->j*5, game->i*5);//mlx_pixel_put (game->mlx,game->mlx_win,game->j*5,game->i*5,  0xff3300);
				drawDDA(game->j*5,game->i*5,game->j*5-10,game->i*5+10,game);
			}
			game->j++;
		}
		game->i++;
	}
	return (0);
}

int	lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	mlx_start(char **map,t_rend *game)
{
	int i;
	char **t_map;
	int k;
	int h; 
	int b;
	int j;
	
	i = 6;
	k = ft_strlen(map[i]);
	while(map[i])
	{
	
		if(k < (int)ft_strlen(map[i]))
			k = ft_strlen(map[i]);
		i++;
	}
	h = i;
	b = 0;
	i = 6;
	j = 0;
	t_map = malloc(sizeof(char *)*h-6);
	while(map[i])
	{
		j = 0;
		t_map[b] = malloc(sizeof(char) *k+1);
		while(map[i][j])
		{
			t_map[b][j] = map[i][j];
			if(t_map[b][j] == ' ')
				t_map[b][j] = '1';
			j++;
		}
		if(k > j)
		{
			while(k > j)
			{
				t_map[b][j] = '1';
				j++;
			}
			t_map[b][j] = '\0';
		}
		i++;
		b++;
	}
	t_map[b] = NULL;
	i = 0;
	while(t_map[i])
		printf("%s\n",t_map[i++]);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx,k*35,lines(t_map)*35,"cub3d");
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", &game->width, &game->height);
	game->black = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/square-1.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/PLA3.xpm", &game->width, &game->height);
	game->map = t_map;
	image_rendering(game);
	mlx_hook(game->mlx_win, 2, 0, &take_key, game);
	//mlx_hook(data.mlx_win, 17, 0, &ft_exit, &data);
	mlx_loop_hook(game->mlx, image_rendering, game);
	mlx_loop(game->mlx);
}