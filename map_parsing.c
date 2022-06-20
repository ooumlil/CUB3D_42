/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:16:54 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/20 16:16:59 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int check_map_is_close(char **map,int i,char c,char p)
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
					if (map[i][j + 1] != '1' && map[i][j + 1] != '0' && map[i][j + 1] != p)
						return (1);
					if (map[i][j - 1] != '1' && map[i][j - 1] != '0'&& map[i][j - 1] != p)
						return (1);
					if (map[i + 1][j] != '1' && map[i + 1][j] != '0'  && map[i + 1][j] != p)
						return (1);
					if (map[i - 1][j] != '1' && map[i - 1][j] != '0'  && map[i - 1][j] != p)
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
	int k;
	char p;
	
	k = 0;
	i = 0;
	j = 0;
	while(six_lines[i])
		if(check_first_sixlines(six_lines[i++]))
				return (printf("error\n"));
	if (check_duble_element(six_lines))
		return (printf("error double element\n"));
	if (check_textur(six_lines))
		return (printf("failed to load texture(s).\n"));
	if (check_colors(six_lines))//////
		return (printf("missing colors\n"));
	i = 6;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != '1' && map[i][j] != '0' 
				&& map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'E'&& map[i][j] != 'W' && map[i][j] != ' ')
					return(printf("error88\n"));
			if(map[i][j] == 'N' || map[i][j] == 'S' ||map[i][j] == 'E' ||map[i][j] == 'W' )
			{
				p = map[i][j];
				k++;
			}
			j++;
		}
		i++;
	}
	if(k != 1)
		return(printf("error int player"));
	if(check_map_is_close(map,6,'0',p))
		return (printf("map not close !!\n"));
	if(check_map_is_close(map,6,p,'0'))
		return (printf("player is not in rghit position !!"));
	return (0);
}