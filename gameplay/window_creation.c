/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/07 13:42:14 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void find_endline(int *x,int *y,t_rend *game)
{
	get_index(game,x,y);
	if(game->direction == 'N')
	{
		while(game->map[*y - 1][*x] == '0' && game->map[*y - 1][*x])
			(*y)--;
		//(*y) *= -1;
	}
	else if(game->direction == 'S')
	{
		while(game->map[*y + 1][*x] == '0' && game->map[*y + 1][*x])
			(*y)++;
		//(*y) *= -1;
		//(*x) *= -1;
	}
	else if(game->direction == 'W')
	{
		while(game->map[*y][*x - 1] == '0' && game->map[*y][*x - 1])
			(*x)--;
		//(*x) *= -1;
	}
	else if(game->direction == 'E')
	{
		while(game->map[*y][*x + 1] == '0' && game->map[*y][*x + 1])
			(*x)++;
		(*x) *= -1;
		//(*y) *= -1;
	}
	return ;
}
void drawDDA(int xA,int yA,int xB,int yB,t_rend *game)
{
	//yB = yA;
	//xB = xA;
	find_endline(&xB,&yB,game);
	yB *= 3;
	xB *= 3;
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
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*3, game->i*3);
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->black, game->j*3, game->i*3);
			if(game->map[game->i][game->j] == game->player)
			{
				int g;
				g  =0;
				while(g++ < 60)
					drawDDA(game->j*3,game->i*3,0,0,game);
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*3, game->i*3);
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
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*3, game->i*3);
			if(game->map[game->i][game->j] == game->player)
			{
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->j*3, game->i*3);//mlx_pixel_put (game->mlx,game->mlx_win,game->j*5,game->i*5,  0xff3300);
			}
			game->j++;
		}
		game->i++;
	}
	return (0);
}
// int draw_minimap(t_rend *game)
// {
// 	int x;
// 	int y;
// 	int i;
// 	int j;
// 	int xa;
// 	int ya;
// 	char **t;
// 	i = 0;
// 	j = 0;
// 	mlx_clear_window(game->mlx,game->mlx_win);
// 	get_index(game,&x,&y);
// 	if(y <= 10 )
// 	{
// 		ya = y;
// 		t = malloc(sizeof(char * ) * y + 1);
// 	}
// 	else
// 	{
// 		ya = y - 10;
// 		t = malloc(sizeof(char * ) * y + 10 +1);
// 	}
// 	while (ya < y + 10)
// 	{
// 		t[i] = malloc(ft_strlen(game->map[ya]));
// 		t[i] = strdup(game->map[ya]);
// 		j = 0;
// 		if(xa <= 10 || xa >= (int)ft_strlen(game->map[ya]))
// 		{
// 			xa = x;
// 		}
// 		else
// 			xa = x - 10;
// 		while(xa < x+10)
// 		{
// 			t[i][j++] = game->map[ya][xa++];
// 		}
// 		t[i][j+1] = '\0';
// 		i++;
// 		ya++;
// 	}
// 	t[i] = NULL;
// 	i = 0;
// 	j = 0;
// 	while(t[i] && t[i + 1])
// 	{
// 		j = 0;
// 		while(t[i][j])
// 		{
// 			if(t[i][j] == '0')
// 				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, j*3, i*3);
// 			if(t[i][j] == '1')
// 				mlx_put_image_to_window(game->mlx, game->mlx_win, game->black, j*3, i*3);
// 			if(t[i][j] == '0')
// 				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, j*3, i*3);
// 			if(t[i][j] == game->player)
// 				mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, j*3, i*3);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
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
	exit(0);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx,1080 ,720,"cub3d");
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", &game->width, &game->height);
	game->black = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/square-1.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/PLA3.xpm", &game->width, &game->height);
	game->map = t_map;
	image_rendering(game);
	//draw_minimap(game);
	//game->direction = game->player;
	mlx_hook(game->mlx_win, 2, 0, &take_key, game);
	//mlx_hook(data.mlx_win, 17, 0, &ft_exit, &data);
	mlx_loop_hook(game->mlx, image_rendering, game);
	//mlx_loop_hook(game->mlx, draw_minimap, game);
	mlx_loop(game->mlx);
}