/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/24 05:56:35 by ooumlil          ###   ########.fr       */
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
            mlx_pixel_put(game->mlx, game->mlx_win, game->pplayer->x+ i-2, game->pplayer->y+j-2, 0xff0000);
            j++;
        }
        i++;
    }
}
void player_directionDDA(int xA,int yA,int xB,int yB,t_rend *game)
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
		mlx_pixel_put(game->mlx,game->mlx_win,round(x),round(y),0x0307fc);
		x += xinc;
		y += yinc;

		step--;
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

float distancebetwenpoint(float x1,float y1,float x2,float y2)
{
	return(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}

void cast_ray(float rayangel,int i,t_rend *m)
{
	m->rays[i].rayAngle = rayangel;
	m->rays[i].washitvertical = FALSE;
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
	float hhitx;
	float hhity;
	int findhorzwall_hit;
	findhorzwall_hit = FALSE;
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
	xintercept =  m->pplayer->x + (yintercept - m->pplayer->y) / tan(rayangel);
	 /////////////////////////////////////////
	ystep = 16;
	if(rayisup)
		ystep *= -1;
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
			hhitx = x_chk;
			hhity = y_chk;
			findhorzwall_hit = TRUE;
			//drawDDA(m->pplayer->x,m->pplayer->y,x_chk,y_chk,m);
			break ;
		}
		else
		{
			x_chk += xstep;
			y_chk += ystep;
		}
	}
	//////////////////////////////////////////////////
	////////////////VIRTICAL//////////////////////////
	//////////////////////////////////////////////////
	int findvir_wall;
	float vhitx;
	float vhity;
	
	findvir_wall = FALSE;

	
	xintercept = floor(m->pplayer->x/16) * 16;
	if(rayisright)
		xintercept += 16;
		
	yintercept =  m->pplayer->y + (xintercept - m->pplayer->x) * tan(rayangel);
	 /////////////////////////////////////////
	xstep = 16;
	if(rayisleft)
		xstep *= -1;
	ystep = 16*tan(rayangel);
	if(rayisup && ystep > 0)
		ystep *= -1;
	if(rayisdown && ystep < 0)
		ystep *= -1;
	float	vx_chk;
	float	vy_chk;

	vx_chk = xintercept;
	vy_chk = yintercept;

	if(rayisleft)
		vx_chk--;
	while (!is_end_window(m, vx_chk, vy_chk))
	{
		if (is_wall(m, vx_chk, vy_chk, '1'))
		{
			vhitx = vx_chk;
			vhity = vy_chk;
			findvir_wall = TRUE;
			//drawDDA(m->pplayer->x,m->pplayer->y,vx_chk,vy_chk,m);
			break ;
		}
		else
		{
			vx_chk += xstep;
			vy_chk += ystep;
		}
	}
	////////////call distance///////////////////////////////
	double horz_dist;
	double vert_dist;
	if(findhorzwall_hit)
		horz_dist = distancebetwenpoint(m->pplayer->x,m->pplayer->y,x_chk,y_chk);
	else
		horz_dist = INT_MAX;
	if(findvir_wall)
		vert_dist = distancebetwenpoint(m->pplayer->x,m->pplayer->y,vx_chk,vy_chk);
	else
		vert_dist = INT_MAX;
	
	if(horz_dist <= vert_dist)
	{
		wallhitx = x_chk;
		wallhity = y_chk;
	}
	else
	{
		wallhitx = vx_chk;
		wallhity = vy_chk;
	}
	///drawDDA(m->pplayer->x,m->pplayer->y,wallhitx,wallhity,m);
	m->rays[i].wallhitx = wallhitx;
	m->rays[i].wallhity = wallhity;
	if(horz_dist < vert_dist)
		m->rays[i].distane = horz_dist;
	else
		m->rays[i].distane = vert_dist;
		m->rays[i].washitvertical = (vert_dist < horz_dist);
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
		drawDDA(m->pplayer->x,m->pplayer->y,m->rays[i].wallhitx,m->rays[i].wallhity,m);
		i++;
		ra += FOV_ANGLE/NUM_RAYS;
		colum++;
	}
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
	draw_square(game);
	player_directionDDA(game->pplayer->x,game->pplayer->y,game->pplayer->x+cos(game->pplayer->rotatangle)*20,game->pplayer->y+sin(game->pplayer->rotatangle)*20,game);
	return(0);
}
void	put_wall(t_rend *m, int wall_h, int i)
{
	t_img	img;
	char	*dst;
	int		y;
	int		x;
	unsigned int c;
	c = 0x03bafc;
	img.img = mlx_new_image(m->mlx, 3, wall_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y != wall_h)
	{
		x = 0;
		while (x != 3)
		{
			dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
			*(unsigned int*)dst = c;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(m->mlx, m->mlx_win, img.img, i, (1080 / 2) - (wall_h / 2));
	mlx_destroy_image(m->mlx, img.img);
}
void projectewall3d(t_rend *m)
{
	int i;
	i = 0;
	float raydist;
	float wallstripheigth;
	float distanceprojplan ;
	distanceprojplan = (1080/2)/tan(FOV_ANGLE/2);
	while(i < NUM_RAYS)
	{
		raydist = m->rays[i].distane;
		wallstripheigth = (16/raydist)*distanceprojplan;
		put_wall(m, (int)fabs((wallstripheigth)), i * 3);
		i++;
	}
}
int	image_rendering(t_rend *game)
{
	float movestep;
	float newx;
	float newy;
	mlx_clear_window(game->mlx,game->mlx_win);
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



	rays(game);
	player_render(game);
	projectewall3d(game);
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