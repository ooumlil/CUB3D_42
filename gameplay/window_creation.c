/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:33:58 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/09 22:44:16 by mfagri           ###   ########.fr       */
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
int player_render(t_rend *game)
{
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x-1*10, game->pplayer->y*10);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->empty, game->pplayer->x*10, game->pplayer->y*10);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->p, game->pplayer->x*10, game->pplayer->y*10);
	drawDDA(game->pplayer->x*10,game->pplayer->y*10,game->pplayer->x*10+cos(game->pplayer->rotatangle)*20,game->pplayer->y*10+sin(game->pplayer->rotatangle)*20,game);
	return(0);
}
int	image_rendering(t_rend *game)
{
	int movestep;
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
		printf("ffd\n");
		//game->pplayer->x -= cos(game->pplayer->rotatangle)*movestep;
		//game->pplayer->y -= sin(game->pplayer->rotatangle)*movestep;
		game->pplayer->rotatangle -= game->pplayer->turn_d * game->pplayer->rotationSpeed; 
		movestep = game->pplayer->wlk_d * game->pplayer->moveSpeed;
		game->pplayer->x -= cos(game->pplayer->rotatangle)*movestep;
		game->pplayer->y -= sin(game->pplayer->rotatangle)*movestep;
	}
	else
		printf("ffs\n");
			
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