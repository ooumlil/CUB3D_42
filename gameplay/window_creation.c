/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/11 23:38:50 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void drawDDA(int xA,int yA,int xB,int yB,t_rend *game)
{
	// yB = yA+3;
	// xB = xA+3;
	//find_endline(&xB,&yB,game);
	// yB *= 3;
	// xB *= 3;
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
		// if(game->map[(int)y][(int)x] == '1')
		// 	break ;
		step--;
	}
	//printf("%f %f-------\n", x, y);
	
	
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
void castSingleRay(float rayAngle,t_rend *m) {
	// Make sure the angle is between 0 and 360 degrees
	rayAngle = normaliseangle(rayAngle);

	// Moving right/left? up/down? Determined by
	// which quadrant the angle is in
	int right = (rayAngle > 2*PI * 0.75 || rayAngle < 2*PI * 0.25);
	//int up = (rayAngle < 0 || rayAngle > PI);

	float angleSin = sin(rayAngle);
	float angleCos = cos(rayAngle);

	// The distance to the block we hit
	int dist = 0;
	// The x and y coord of where the ray hit the block
	float xHit = 0, yHit = 0;
	// The x-coord on the texture of the block,
	// i.e. what part of the texture are we going to render
	//var textureX;
	// The (x,y) map coords of the block
	//float wallX;
	//float wallY;

	// First check against the vertical map/wall lines
	// we do this by moving to the right or left edge
	// of the block we’re standing in and then moving
	// in 1 map unit steps horizontally. The amount we have
	// to move vertically is determined by the slope of
	// the ray, which is simply defined as sin(angle) / cos(angle).

	// The slope of the straight line made by the ray
	float slope = angleSin / angleCos;
	// We move either 1 map unit to the left or right
	float dX = right ? 1 : -1;
	// How much to move up or down
	float dY = dX * slope;

	// Starting horizontal position, at one
	// of the edges of the current map block
	float x = right ? ceil(m->pplayer->x) : floor(m->pplayer->x);
	// Starting vertical position-> We add the small horizontal
	// step we just made, multiplied by the slope
	float y = m->pplayer->y + (x - m->pplayer->x) * slope;

	while (x >= 0 && x < m->mapx && y >= 0 && y < lines(m->map))
	{
		int wallX = floor(x + (right ? 0 : -1));
		int wallY = floor(y);

		// Is this point inside a wall block?
		if (m->map[wallY][wallX] != '0') {
			float distX = x - m->pplayer->x;
			float distY = y - m->pplayer->y;
			// The distance from the player to this point, squared
			dist = sqrt(distX*distX + distY*distY);

			// Save the coordinates of the hit. We only really
			// use these to draw the rays on minimap
			xHit = x;
			yHit = y;
			break;
		}
		x += dX;
		y += dY;
	}

	// Horizontal run snipped,
	// basically the same as vertical run

	if (dist)
		drawDDA(m->pplayer->x*10,m->pplayer->y*10,xHit*10,yHit*10,m);
		//rayangle += FOV_ANGLE/NUM_RAYS/2;
	//drawRay(xHit, yHit);
}
int maphaswall(float x,float y,t_rend *m)
{
	if(x < 0 || x > m->mapx || y < 0 || y > lines(m->map))
		return (1);
	int mx = floor(x);
	int my = floor(y);
	if(m->map[mx][my] == '1')
		return (1);
	return (0);
}
void drawray(t_rend *game)
{
	int py;
	int px;
	get_index(game,&px,&py);
	int r,dof;
	float rx,ry,ra,xo,yo;
	ra =PI/2;
	r = 0;
	while(r < 1)
	{
		r++;
		dof=0;
		float atan=-1/tan(ra);
		if(ra>PI)
		{
			ry=(((int)py>>6)<<6)-0.0001;
			rx=(py-ry)*atan+px;
			yo = -64;
			xo=-yo*atan;
		}
		if(ra<PI)
		{
			ry=(((int)py>>6)<<6)+64;
			rx=(py-ry)*atan+px;
			yo = 64;
			xo=-yo*atan;
		}
		if(ra == 0 || ra == PI )
		{
			rx=px;
			ry=py;
			dof=8;	
		}
		// while(dof<8)
		// {
		// 	mx = (int)(rx)>>6;
		// 	my(int)(ry)>>6;
		// 	mp=my*lines(game->map)+mx;
		// 	//if(game->map[] )
		// }
		drawDDA(px*10,py*10,rx*10,ry*10,game);
	}
}
// void find_endline(int *x,int *y,t_rend *game)
// {
// 	get_index(game,x,y);
// 	if(game->direction == 'N')
// 	{
// 		while(game->map[*y - 1][*x] == '0' && game->map[*y - 1][*x])
// 			(*y)--;
// 		//(*y) *= -1;
// 	}
// 	else if(game->direction == 'S' && *y != lines(game->map))
// 	{
// 		while(game->map[*y + 1][*x] == '0' && game->map[*y + 1][*x])
// 			(*y)++;
// 		(*y) *= -1;
// 		(*x) *= -1;
// 	}
// 	else if(game->direction == 'W')
// 	{
// 		while(game->map[*y][*x - 1] == '0' && game->map[*y][*x - 1])
// 			(*x)--;
// 	}
// 	else if(game->direction == 'E')
// 	{
// 		while(game->map[*y][*x + 1] == '0' && game->map[*y][*x + 1] && *x != (int)ft_strlen(game->map[*y]))
// 			(*x)++;
// 		(*x) *= -1;
// 	}
// 	return ;
// }
float distensb(float x1,float y1,float x2,float y2)
{
	return(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}
int player_render(t_rend *game)
{
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x-1*10, game->pplayer->y*10);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x*10, game->pplayer->y*10);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->pplayer->x*10, game->pplayer->y*10);
	mlx_pixel_put(game->mlx,game->mlx_win,game->pplayer->x*10,game->pplayer->y*10,0xff3300);
	drawDDA(game->pplayer->x*10,game->pplayer->y*10,game->pplayer->x*10+cos(game->pplayer->rotatangle)*20,game->pplayer->y*10+sin(game->pplayer->rotatangle)*20,game);
	return(0);
}
// float normaliseangle(float angle)
// {
// 	angle = remainder(angle ,(2*PI));
// 	if(angle < 0)
// 	{
// 		angle = (2*PI) + angle;
// 	}
// 	return (angle);
// }
void c_r(float rayangle,int i,t_rend *m)
{
	rayangle = normaliseangle(rayangle);
	
	int israyfacingdown = rayangle > 0 && rayangle < PI;
	int israyfacingup = !israyfacingdown;
	int israyfacingright = rayangle < 0.75 *PI || rayangle > 0.25*PI;
	int israyfacingleft = !israyfacingright;
	float xintercept,yintercept;
	float xstep,ystep;
	//////////////////////////////
	int foundhorzwallhitt = 0;
	float howhx = 0;
	float howhy = 0;
	int howcontent = 0;
	//////////////////////////////
	//find y
	yintercept = floor(m->pplayer->y/10)*10;
	yintercept += israyfacingdown ? 10  : 0;
	//////////////////////////////
	xintercept = m->pplayer->x + (yintercept - m->pplayer->y)/tan(rayangle);
	/////////////////////////////
	ystep = 10;
	ystep *= israyfacingup ? -1 : 1;
	////////////////////////////////////
	xstep = 10/tan(rayangle);
	xstep *= (israyfacingleft && xstep > 0) ? -1 : 1;
	xstep *= (israyfacingright && xstep < 0) ? -1 : 1;

	//////////////////////////////////////
	float nexthorx = xintercept;
	float nexthory = yintercept;

	////incremnt steps
	while(nexthorx >= 0 && nexthorx <= m->mapx && nexthory >= 0 && nexthory <= lines(m->map))
	{
		float xtocheck = nexthorx;
		float ytocheck = nexthory + (israyfacingup ? -1 :0);
		if(maphaswall(xtocheck,ytocheck,m))
		{
			//////is wall
			//puts("wall");
			howhx = nexthorx;
			howhy = nexthory;
			howcontent = (int)(m->map[(int)floor(ytocheck/10)][(int)floor(xtocheck/10)]);
			foundhorzwallhitt = 1;
			break;
		}
		else
		{
			nexthorx += xstep;
			nexthory += ystep;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	//virticale part////////
	//////////////////////////////
	int foundvorzwallhitt = 0;
	float vowvx = 0;
	float vowvy = 0;
	int viwcontent = 0;
	//////////////////////////////
	//find y
	xintercept = floor(m->pplayer->x/10)*10;
	xintercept += israyfacingright ? 10  : 0;
	//////////////////////////////
	yintercept = m->pplayer->y + (xintercept - m->pplayer->x)*tan(rayangle);
	/////////////////////////////
	xstep = 10;
	xstep *= israyfacingleft ? -1 : 1;
	////////////////////////////////////
	ystep = 10*tan(rayangle);
	ystep *= (israyfacingup && ystep > 0) ? -1 : 1;
	ystep *= (israyfacingdown && ystep < 0) ? -1 : 1;

	//////////////////////////////////////
	float nextvorx = xintercept;
	float nextvory = yintercept;

	////incremnt steps
	while(nextvorx >= 0 && nextvorx <= m->mapx && nextvory >= 0 && nextvory < lines(m->map))
	{
		float ytocheck = nextvory;
		float xtocheck = nextvorx + (israyfacingleft ? -1 :0);
		if(maphaswall(xtocheck,ytocheck,m))
		{
			//////is wall
			vowvx = nextvorx;
			vowvy = nextvory;
			viwcontent = (int)(m->map[(int)floor(ytocheck/10)][(int)floor(xtocheck/10)]);
			foundvorzwallhitt = 1;
			break;
		}
		else
		{
			nextvorx += xstep;
			nextvory += ystep;
		}
	}
	/////////h %% v d/////
	float horhd = foundhorzwallhitt ? distensb(m->pplayer->x,m->pplayer->y,howhx,howhy): INT_MAX;
	float vihd = foundvorzwallhitt  ? distensb(m->pplayer->x,m->pplayer->y,vowvx,vowvy): INT_MAX;
	if(vihd < horhd)
	{
		m->rays[i].distane = vihd;
		m->rays[i].wallhitx = vowvx;
		m->rays[i].wallhity = vowvy;
		m->rays[i].wallhitcomtent = viwcontent;
		m->rays[i].washitvertical = 1;
	}
	else
	{
		m->rays[i].distane = horhd;
		m->rays[i].wallhitx = howhx;
		m->rays[i].wallhity = howhy;
		m->rays[i].wallhitcomtent = howcontent;
		m->rays[i].washitvertical = 0;
	}
	m->rays[i].rayAngle = rayangle;
	// down left righte up//
}
void cast_rays(t_rend *m)
{
	int i = 0;
	int colum = 0;
	float rayangle =  m->pplayer->rotatangle - (FOV_ANGLE/2);
	//rays = [];
	while(i < NUM_RAYS)
	{ 
		//c_r(rayangle,i,m);
		//puts("dd");
		castSingleRay(rayangle,m);
		//drawDDA(m->pplayer->x*10,m->pplayer->y*10,m->rays[i].wallhitx*10,m->rays[i].wallhity*10,m);
		rayangle += FOV_ANGLE/NUM_RAYS;
		colum++;
		i++;
	}
	return;
}
int	image_rendering(t_rend *game)
{
	int movestep;
	mlx_clear_window(game->mlx,game->mlx_win);
	game->pplayer->rotatangle += game->pplayer->turn_d * game->pplayer->rotationSpeed; 
	movestep = game->pplayer->wlk_d * game->pplayer->moveSpeed;
	game->pplayer->x += cos(game->pplayer->rotatangle)*movestep;
	game->pplayer->y += sin(game->pplayer->rotatangle)*movestep;
	if(hit_thewall(game))
	{
		if(game->pplayer->wlk_d < 0)
			game->pplayer->wlk_d +=1;
		else 
			game->pplayer->wlk_d -=1;
		//printf("ffd\n");
		//game->pplayer->x -= cos(game->pplayer->rotatangle)*movestep;
		//game->pplayer->y -= sin(game->pplayer->rotatangle)*movestep;
		game->pplayer->rotatangle -= game->pplayer->turn_d * game->pplayer->rotationSpeed; 
		movestep = game->pplayer->wlk_d * game->pplayer->moveSpeed;
		game->pplayer->x -= cos(game->pplayer->rotatangle)*movestep;
		game->pplayer->y -= sin(game->pplayer->rotatangle)*movestep;
	}
	else
		//printf("ffs\n");
			
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
			
			else//if(game->map[game->i][game->j] == game->player)
			{
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->j*10, game->i*10);
				//mlx_put_image_to_window(game->mlx, game->mlx_win, game->black, game->j*10, game->i*10);
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
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->wall, game->j*10, game->i*10);
			if(game->map[game->i][game->j] == '1')
				game->i = game->i;
			game->j++;
		}
		game->i++;
	}
	// printf("%d\n",game->pplayer->turn_d);
	player_render(game);
	cast_rays(game);
	game->pplayer->turn_d = 0;
	game->pplayer->wlk_d = 0;
	// printf("%d\n",game->pplayer->turn_d);
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
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx,1080 ,720,"cub3d");
	game->wall = mlx_xpm_file_to_image(game->mlx, "img/P.xpm", &game->width, &game->height);
	game->black = mlx_xpm_file_to_image(game->mlx, "img/black1.xpm", &game->width, &game->height);
	game->empty = mlx_xpm_file_to_image(game->mlx, "img/square-1.xpm", &game->width, &game->height);
	game->spaces = mlx_xpm_file_to_image(game->mlx, "img/yellow.xpm", &game->width, &game->height);
	game->p = mlx_xpm_file_to_image(game->mlx, "img/PLA3.xpm", &game->width, &game->height);
	game->map = t_map;
	player_init(game);
	image_rendering(game);
	//player_render(game);
	//draw_minimap(game);
	//game->direction = game->player;
	//mlx_hook(data.mlx_win, 17, 0, &ft_exit, &data);
	mlx_hook(game->mlx_win, 2, 0, &take_key, game);
	mlx_loop_hook(game->mlx, image_rendering, game);
	//mlx_loop_hook(game->mlx, player_render, game);
	//mlx_hook(game->mlx_win, 2, 0, &take_key2, game);
	//mlx_loop_hook(game->mlx, draw_minimap, game);
	mlx_loop(game->mlx);
}