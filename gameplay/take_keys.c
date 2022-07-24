/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:26:19 by mfagri            #+#    #+#             */
/*   Updated: 2022/07/24 01:13:41 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


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
int keys(int key , t_rend *m)
{
	if(key == 13)
	{
		m->pplayer->wlk_d = 1;
	}
	if(key == 1)
	{
		m->pplayer->wlk_d = -1;
	}
	if(key == 0)
	{
		m->pplayer->wlk_d = 1;
	}
	if(key == 2)
	{
		m->pplayer->wlk_d = -1;
	}
	if(key == 124)
	{
		m->pplayer->turn_d = 1;
        // if (m->pplayer->rotatangle >= PI*2)
        //     m->pplayer->rotatangle -= (2 * PI);
	}
	if(key == 123)
	{
		m->pplayer->turn_d = -1;
		//  if (m->pplayer->rotatangle <= 0)
        //     m->pplayer->rotatangle += (2 * PI);
	}
	if(key == 53)
		exit(0);
	return (0);
}
int keys_2(int key , t_rend *m)
{
	if(key == 13)
	{
		m->pplayer->wlk_d = 0;
	}
	if(key == 1)
	{
		m->pplayer->wlk_d = 0;
	}
	if(key == 0)
	{
		m->pplayer->wlk_d = 0;
	}
	if(key == 2)
	{
		m->pplayer->wlk_d = 0;
	}
	if(key == 124)
	{
		m->pplayer->turn_d = 0;
	}
	if(key == 123)
	{
		m->pplayer->turn_d = 0;
	}
	return (0);
}