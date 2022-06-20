/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:16:54 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/20 12:09:44 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int check_map_is_close(char **map,int i,char c)
{
		int k;
		int j;
		
		k = 0;
		while(map[k])
			k++;
		while(map[i])
		{
			j = 0;
			while(map[i][j])
			{
				if (map[i][0] == c)
					return (1);
				if (map[6][j] != '1' && map[6][j] != ' ' && i == 6)
					return (1);
				if (map[k - 1][j] != '1' && map[k - 1][j] != ' ' && i == k - 1)
					return (1);
				if (map[i][j] == c && i != 6 && i != k - 1)
				{
					if (map[i][j + 1] != '1' && map[i][j + 1] != '0' && map[i][j + 1] != 'E' && map[i][j + 1] != 'S' && map[i][j + 1] != 'W')
						return (1);
					if (map[i][j - 1] != '1' && map[i][j - 1] != '0'&& map[i][j - 1] != 'E' && map[i][j - 1] != 'S' && map[i][j - 1] != 'W')
						return (1);
					if (map[i + 1][j] != '1' && map[i + 1][j] != '0'  && map[i + 1][j] != 'E' && map[i + 1][j] != 'S' && map[i + 1][j] != 'W')
						return (1);
					if (map[i - 1][j] != '1' && map[i - 1][j] != '0'  && map[i - 1][j] != 'E' && map[i - 1][j] != 'S' && map[i - 1][j] != 'W')
						return (1);
				}
				j++;
			}
			i++;
		}
		return (0);
}
int map_parsing(char **six_lines,char **map)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while(six_lines[i])
		if(check_first_sixlines(six_lines[i++]))
				return (printf("error\n"));
	if (check_duble_element(six_lines))
		return (printf("error double element\n"));
	if (check_textur(six_lines))
		return (printf("failed to load texture(s).\n"));
	if (check_colors(six_lines))
		return (printf("missing colors\n"));
	if(check_map_is_close(map,6,'0'))
		return (printf("map not close !!\n"));
	return (0);
}