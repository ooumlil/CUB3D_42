/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:26:19 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/25 19:06:41 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// void	ft_exit()
// {
// 	exit (0);
// }
void	get_index(t_rend *m, int *x, int *y)
{
	*y = 6;
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
	// if (game->map[y][x - 1] == 'C')
	// {
	// 	game->map[y][x - 1] = p;
	// 	game->map[y][x] = '0';
	// }
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
	// if (game->map[y + 1][x] == 'C')
	// {
	// 	game->map[y + 1][x] = p;
	// 	game->map[y][x] = '0';
	// }
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
	// if (game->map[y][x + 1] == 'C')
	// {
	// 	game->map[y][x + 1] = p;
	// 	game->map[y][x] = '0';
	// }
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
	// if (map->map[y - 1][x] == 'C')
	// {
	// 	map->map[y - 1][x] = p;
	// 	map->map[y][x] = '0';
	// }
	if (m->map[y - 1][x] == '0')
	{
		m->map[y - 1][x] = m->player;
		m->map[y][x] = '0';
	}
}

int	take_key(int key, t_rend *m)
{
	if (key == 0)
	{
		key_0(m, m->player);
	}
	if (key == 1)
		key_1(m, m->player);
	if (key == 2)
		key_2(m, m->player);
	if (key == 13)
		key_13(m);
	if (key == 53)
		exit (0);
	return (key);
}