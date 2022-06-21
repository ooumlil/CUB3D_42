/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 21:57:41 by ooumlil           #+#    #+#             */
/*   Updated: 2022/06/21 22:33:01 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_first_sixlines(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && s[2] == ' ')
		return (0);
	else if (s[0] == 'S' && s[1] == 'O' && s[2] == ' ')
		return (0);
	else if (s[0] == 'W' && s[1] == 'E' && s[2] == ' ')
		return (0);
	else if (s[0] == 'E' && s[1] == 'A' && s[2] == ' ')
		return (0);
	else if (s[0] == 'F' && s[1] == ' ')
		return (0);
	else if (s[0] == 'C' && s[1] == ' ')
		return (0);
	else
		return (1);
}

int	check_textur(char **six_lines)
{
	int		i;
	char	*s;
	int		j;

	i = 0;
	j = 0;
	while (six_lines[i])
	{
		j = 0;
		if (!ft_strchr(six_lines[i], ','))
		{
			s = ft_strchr(six_lines[i], ' ');
			if (s[j] == ' ')
				while (s[j] == ' ')
					++s;
			if (open(s, O_RDWR, 777) == -1
				|| strcmp(ft_strrchr(s, '.'), ".xpm") != 0)
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	check_duble_element(char **six_lines)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (six_lines[i])
	{
		j = i + 1;
		while (six_lines[j])
		{
			if (!strncmp(six_lines[i], six_lines[j], 2))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_final_check(char **map)
{
	int		j;
	char	**six_lines;

	if (!map)
		return (1);
	j = -1;
	six_lines = malloc(sizeof(char *) * 6 + 1);
	while (map[++j] && j < 6)
	{
		six_lines[j] = malloc(sizeof(char) * ft_strlen(map[j]));
		six_lines[j] = strdup(map[j]);
	}
	six_lines[j] = NULL;
	if (map_parsing(six_lines, map))
		return (1);
	return (0);
}
