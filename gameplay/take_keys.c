/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:26:19 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/11 21:04:42 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// void	ft_exit()
// {
// 	exit (0);
// }
int hit_thewall(t_rend *m)
{
	if((int)floor(m->pplayer->x) >= m->mapx || (int)floor(m->pplayer->x)  < 0 || (int)floor(m->pplayer->y)  < 0 ||(int)floor(m->pplayer->y) > lines(m->map))
	{
		//puts("toool");
		return (1);
	}
	else if(m->map[(int)floor(m->pplayer->y)][(int)floor(m->pplayer->x)] == '1')
	{
		//printf("{%c}\n",m->map[(int)floor(m->pplayer->y)][(int)floor(m->pplayer->x)]);
		return (1);
	}
	return (0);
}
void	get_index(t_rend *m, int *x, int *y)
{
	*y = 0;
	while (m->map[*y])
	{
		*x = 0;
		while (m->map[*y][*x])
		{
			if (m->map[*y][*x] == m->player)
				return ;
			(*x)++;
		}
		(*y)++;
	}
}
void	key_0(t_rend *game, char p)
{
	int		x;
	int		y;

	get_index(game, &x, &y);
	if (game->map[y][x - 1] == '0')
	{
		game->map[y][x - 1] = p;
		game->map[y][x] = '0';
	}
}

void	key_1(t_rend *game, char p)
{
	int		x;
	int		y;

	get_index(game, &x, &y);
	if (game->map[y + 1][x] == '0')
	{
		game->map[y + 1][x] = p;
		game->map[y][x] = '0';
	}
}

void	key_2(t_rend *game, char p)
{
	int		x;
	int		y;

	get_index(game, &x, &y);
	if (game->map[y][x + 1] == '0')
	{
		game->map[y][x + 1] = p;
		game->map[y][x] = '0';
	}
}

void	key_13(t_rend *m)
{
	int		x;
	int		y;

	get_index(m, &x, &y);
	if (m->map[y - 1][x] == '0')
	{
		m->map[y - 1][x] = m->player;
		m->map[y][x] = '0';
	}
}
int take_key2(int key, t_rend *m)
{
	if (key == 0)
		m->pplayer->wlk_d = 0;
	else if (key == 1)
		m->pplayer->wlk_d = 0;
	else if (key == 2)
		m->pplayer->wlk_d = 0;
	else if (key == 13)
		m->pplayer->wlk_d = 0;
	else if(key == 123)
		m->pplayer->turn_d = 0;
	else if(key == 124)
		m->pplayer->turn_d = 0;
	return(key);
}
int take_key_1(int key, t_rend *m)
{
	if (key == 0)
	{
		if(m->map[m->pplayer->y][m->pplayer->x -1] != '1')
			m->pplayer->x -= 1;
	}
	else if (key == 1)
		m->pplayer->wlk_d += 1;
	else if (key == 2)
	{
		if(m->map[m->pplayer->y][m->pplayer->x + 1] != '1')
			m->pplayer->x += 1;
	}
	else if (key == 13)
	{
		m->pplayer->wlk_d -= 1;
	}
	else if(key == 123)
	{
		m->pplayer->turn_d -= 1;
	}
	else if(key == 124)
	{
		m->pplayer->turn_d += 1;
	}
	else if (key == 53)
		exit (0);
	return(key);
}

int	 take_key(int key, t_rend *m)
{
	// if (key == 0)
	// 	key_0(m, m->player);
	// if (key == 1)
	// 	key_1(m, m->player);
	// if (key == 2)
	// 	key_2(m, m->player);
	// if (key == 13)
	// 	key_13(m);
	// if(key == 126)
	// 	m->direction = 'N';
	// if(key == 125)
	// 	m->direction = 'S';
	// if(key == 123)
	// 	m->d += 6;
	// if(key == 124)
	// 	m->d -= 6;
	// if (key == 53)
	// 	exit (0);
	// // else
	// // 	printf("%d\n",key);
	take_key_1(key,m);
	return (key);
}