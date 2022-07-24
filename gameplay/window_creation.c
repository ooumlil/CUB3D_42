/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/24 01:22:09 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
int		is_end_window(t_rend *m, double x, double y)
{
	if (x < 0 || x >= m->mapx * 16 ||
		y < 0 || y >= lines(m->map) * 16)
		return (TRUE);
	return (FALSE);
}
int		is_wall(t_rend *m, int x, int y, char identf)
{
	int	grid_x;
	int	grid_y;

	if (is_end_window(m, x, y))
		return (TRUE);
	grid_x = floor(x / 16);
	grid_y = floor(y / 16);
	if (grid_x >= m->mapx || grid_y >= lines(m->map))
		return (TRUE);
	if (m->map[grid_y][grid_x] == identf)
		return (TRUE);
	return (FALSE);
}

int			ray_facing(double angle, int way)
{
	int	up;
	int	down;
	int	left;
	int	right;

	down = (angle > 0 && angle < PI) ? TRUE : FALSE;
	up = !(down) ? TRUE : FALSE;
	left = (angle > PI / 2 && angle < 3 * PI / 2) ? TRUE : FALSE;
	right = !left ? TRUE : FALSE;
	if (way == ray_up)
		return (up);
	else if (way == ray_down)
		return (down);
	else if (way == ray_left)
		return (left);
	else if (way == ray_right)
		return (right);
	return (-1);
}
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
            mlx_pixel_put(game->mlx, game->mlx_win, game->pplayer->x+ i, game->pplayer->y+j, 0xff0000);
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
		// if(game->map[(int)y/16][(int)x/16] == '1')
		// 	break;
		mlx_pixel_put(game->mlx,game->mlx_win,round(x),round(y),0xff3300);
		x += xinc;
		y += yinc;

		step--;
	}	
}
float normaliseangle(float angle)
{
	angle = remainder(angle ,(2*PI));
	if(angle < 0)
	{
		angle = (2*PI) + angle;
	}
	return (angle);
}
void cast_ray(float rayangel,int i,t_rend *m)
{
	m->rays[i].rayAngle = rayangel;
	rayangel = normaliseangle(rayangel);
	int wallhitx;
	int wallhity;
	int rayisup;
	int rayisdown;
	int rayisleft;
	int rayisright;
	float distance;
	float ystep;
	float xstep; 
	float yintercept;
	float xintercept;
	float hitx;
	float hity;
	int fondwall_hit;
	fondwall_hit = FALSE;
	rayisdown = 0;
	rayisright = 0;
	wallhitx = 0;
	wallhity =0;
	distance = 0;
	if(rayangel  > 0 && rayangel < PI)
		rayisdown = 1;
	rayisup = !rayisdown;
	if(rayangel < 0.5 * PI || rayangel > 1.5 * PI)
		rayisright = 1;
	rayisleft = !rayisright;
	//drawDDA(m->pplayer->x*16,m->pplayer->y*16,m->pplayer->x*16+cos(rayangel)*30,m->pplayer->y*16+sin(rayangel)*30,m);
	////////////////////////////////////////////
	//////HORIZONTAL RAY !//////////////////////
	////////////////////////////////////////////
	
	yintercept = floor(m->pplayer->y/16) * 16;
	if(rayisdown)
		yintercept += 16;
	//yintercept += ray_facing(rayangel, ray_down) ? 16 : 0;
	xintercept =  m->pplayer->x + (yintercept - m->pplayer->y) / tan(rayangel);
	 /////////////////////////////////////////
	ystep = 16;
	if(rayisup)
		ystep *= -1;
	//ystep *=ray_facing(rayangel, ray_up) ? -1 : 1;
	
	xstep = 16/tan(rayangel);
	if(rayisleft && xstep > 0)
		xstep *= -1;
	if(rayisright && xstep < 0)
		xstep *= -1;
	float	x_chk;
	float	y_chk;

	x_chk = xintercept;
	y_chk = yintercept;

	if(rayisup)
		y_chk--;
	while (!is_end_window(m, x_chk, y_chk))
	{
		if (is_wall(m, x_chk, y_chk, '1'))
		{
			hitx = x_chk;
			hity = y_chk;
			fondwall_hit = TRUE;
			drawDDA(m->pplayer->x,m->pplayer->y,x_chk,y_chk,m);
			break ;
		}
		else
		{
			// xintercept += xstep;
			// yintercept += ystep;
			x_chk += xstep;
			y_chk += ystep;
		}
	}
}
void rays(t_rend *m)
{
	int colum;
	colum = 0;
	float ra;
	ra = m->pplayer->rotatangle - (FOV_ANGLE/2);
	int i;
	i = 0;
	while(i < 1)
	{
		cast_ray(ra,i,m);
		i++;
		ra += FOV_ANGLE/NUM_RAYS;
		colum++;
	}
	// 	i = 0;
	// float plane = (360 / 2) / (tan(FOV_ANGLE / 2));
	// while (i < 1)
	// {
	// 	ra = m->pplayer->rotatangle +
	// 		atan2(i - NUM_RAYS / 2, plane);
	// 	//ra = ft_normalize_angle(vars->ray[i]->ray_angle);
	// 	//check_closest_wall(vars, vars->ray[i], vars->ray[i]->ray_angle);
	// 	cast_ray(ra,i,m);
	// 	i++;
	// }
}
int haswallat(int x,int y,t_rend *m)
{
	if(x/16 < 0 || x/16 > m->mapx || y/16 < 0 || y/16 > lines(m->map))
		return (1);
	if(m->map[y/16][x/16] == '1')
		return (1);
	return (0);
}
int player_render(t_rend *game)
{
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x-1*16, game->pplayer->y*10);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x*10, game->pplayer->y*10);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->pplayer->x*10, game->pplayer->y*10);
	//mlx_pixel_put(game->mlx,game->mlx_win,game->pplayer->x*10,game->pplayer->y*10,0xff3300);
	//DrawCircle(game->pplayer->x*10, game->pplayer->y*10,2,game);
	draw_square(game);
	//drawDDA(game->pplayer->x,game->pplayer->y,game->pplayer->x+cos(game->pplayer->rotatangle)*20,game->pplayer->y+sin(game->pplayer->rotatangle)*20,game);
	return(0);
}
int	image_rendering(t_rend *game)
{
	float movestep;
	float newx;
	float newy;
	mlx_clear_window(game->mlx,game->mlx_win);
	// if (game->pplayer->rotatangle > PI*2)
    //         game->pplayer->rotatangle -= (2 * PI);
	// else if (game->pplayer->rotatangle < 0)
    //         game->pplayer->rotatangle += (2 * PI);
	game->pplayer->rotatangle += game->pplayer->turn_d * game->pplayer->rotationSpeed;
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
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*16, game->i*16);
			if(game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*16, game->i*16);
			
			else
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*16, game->i*16);
			game->j++;
		}
		game->i++;
	}
	// game->i = 0;
	// while(game->map[game->i])
	// {
	// 	game->j = 0;
	// 	while(game->map[game->i][game->j])
	// 	{
	// 		if(game->map[game->i][game->j] == '0')
	// 			mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*16, game->i*16);
	// 		if(game->map[game->i][game->j] == '1')
	// 			game->i = game->i;
	// 		game->j++;
	// 	}
	// 	game->i++;
	// }
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
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/New-Project (2).xpm", &game->width, &game->height);
	game->black = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/Project.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/PLA3.xpm", &game->width, &game->height);
	player_init(game);
	image_rendering(game);
	mlx_hook(game->mlx_win, 2, 0, &keys, game);
	mlx_hook(game->mlx_win, 3, 0, &keys_2, game);
	mlx_loop_hook(game->mlx, image_rendering, game);
	mlx_loop(game->mlx);
}