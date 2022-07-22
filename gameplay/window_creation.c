/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/22 18:47:45 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
void DrawCircle(int x, int y, int r,t_rend *m)
{
      //static const double PI = 3.1415926535;
      double i, angle, x1, y1;

      for(i = 0; i < 360; i += 0.1)
      {
            angle = i;
            x1 = r * cos(angle * PI / 180);
            y1 = r * sin(angle * PI / 180);
            mlx_pixel_put(m->mlx,m->mlx_win,x + x1, y + y1, 0xff3300);
      }
}
void draw_square(t_rend *game)
{
     int    i = 0;
     int    j = 0;
 
    while(i < 4)
    {
        j = 0;
        while(j < 4)
        {
            mlx_pixel_put(game->mlx, game->mlx_win, game->pplayer->x*10 + i, game->pplayer->y*10+j, 0xff0000);
            j++;
        }
        i++;
    }
}
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
		if(game->map[(int)y/10][(int)x/10] == '1')
			break;
		mlx_pixel_put(game->mlx,game->mlx_win,round(x),round(y),0xff3300);
		x += xinc;
		y += yinc;

		step--;
	}	
}
void cast_ray(float rayangel,int i,t_rend *m)
{
	m->rays[i].rayAngle = rayangel;
	drawDDA(m->pplayer->x*10,m->pplayer->y*10,m->pplayer->x*10+cos(rayangel)*300,m->pplayer->y*10+sin(rayangel)*300,m);
	
}
void rays(t_rend *m)
{
	int colum;
	colum = 0;
	float ra;
	ra = m->pplayer->rotatangle - (FOV_ANGLE/2);
	int i;
	i = 0;
	while(i < NUM_RAYS)
	{
		cast_ray(ra,i,m);
		i++;
		ra += FOV_ANGLE/NUM_RAYS;
		colum++;
	}	
}
int haswallat(int x,int y,t_rend *m)
{
	if(x < 0 || x > m->mapx || y < 0 || y > lines(m->map))
		return (1);
	if(m->map[y][x] == '1')
		return (1);
	return (0);
}
int player_render(t_rend *game)
{
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x-1*10, game->pplayer->y*10);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x*10, game->pplayer->y*10);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->pplayer->x*10, game->pplayer->y*10);
	//mlx_pixel_put(game->mlx,game->mlx_win,game->pplayer->x*10,game->pplayer->y*10,0xff3300);
	//DrawCircle(game->pplayer->x*10, game->pplayer->y*10,2,game);
	draw_square(game);
	drawDDA(game->pplayer->x*10,game->pplayer->y*10,game->pplayer->x*10+cos(game->pplayer->rotatangle)*20,game->pplayer->y*10+sin(game->pplayer->rotatangle)*20,game);
	return(0);
}
int	image_rendering(t_rend *game)
{
	game->pplayer->rotatangle += game->pplayer->turn_d * game->pplayer->rotationSpeed;
	float movestep;
	float newx;
	float newy;
	movestep = game->pplayer->wlk_d * game->pplayer->moveSpeed;
	newx = game->pplayer->x + cos(game->pplayer->rotatangle) * movestep;
	newy = game->pplayer->y + sin(game->pplayer->rotatangle) * movestep;
	if(!haswallat(floor(newx),floor(newy),game))
	{
		game->pplayer->x = newx;
		game->pplayer->y = newy;
	}
	game->i = 0;
	while(game->map[game->i])
	{
		game->j = 0;
		while (game->map[game->i][game->j])
		{
			if(game->map[game->i][game->j] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->black, game->j*10, game->i*10);
			
			else
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*10, game->i*10);
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
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == '1')
				game->i = game->i;
			game->j++;
		}
		game->i++;
	}
	player_render(game);
	rays(game);
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
	game->mapx = k;
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
		}
		t_map[b][j] = '\0';
		i++;
		b++;
	}
	t_map[b] = NULL;
	i = 0;
	while(t_map[i])
		printf("%s\n",t_map[i++]);
	// exit(0);
	game->map = t_map;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx,1080 ,720,"cub3d");
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", &game->width, &game->height);
	game->black = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/square-1.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/PLA3.xpm", &game->width, &game->height);
	player_init(game);
	image_rendering(game);
	mlx_hook(game->mlx_win, 2, 0, &keys, game);
	mlx_hook(game->mlx_win, 3, 0, &keys_2, game);
	mlx_loop_hook(game->mlx, image_rendering, game);
	mlx_loop(game->mlx);
}