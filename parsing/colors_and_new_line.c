/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_and_new_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:25:06 by ooumlil           #+#    #+#             */
/*   Updated: 2022/06/24 16:10:49 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_space_colors(char *s, int *k)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != ' ' && s[i])
	{
		if (s[i] != ',' && !ft_isdigit(s[i]))
			return (1);
		if (s[i] == ',')
			(*k)++;
		i++;
	}
	if (s[i] == ' ')
		return (1);
	return (0);
}

int	check_linebyline(char *s, int i, char *map)
{
	int		k;
	char	*d;

	d = malloc(10000);
	k = 0;
	while (s[i] != '\n')
		d[k++] = s[i++];
	d[k] = '\0';
	if (!strncmp(d, map, ft_strlen(d)))
		return (free(d), 1);
	return (free(d), 0);
}

int	ft_check_new_line_1(char *map, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
		{
			i++;
			while (s[i] == '\n')
				i++;
			if (check_linebyline(s, i, map))
				break ;
		}
	}
	return (i);
}

int	ft_check_new_line(char **map, char *s)
{
	int	i;
	int	c;

	i = ft_check_new_line_1(map[6], s);
	c = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			c++;
		i++;
	}
	i = 0;
	while (map[i])
		i++;
	if (i - 6 - 1 != c)
		return (printf("Invalid Map : New Line.\n"));
	return (0);
}

int	check_colors(char **six_lines, int i, int k, int j)
{
	char	**tmp;
	char	*s;

	while (six_lines[i])
	{
		if (ft_strchr(six_lines[i], ','))
		{
			s = ft_strchr(six_lines[i], ' ');
			++s;
			if (check_space_colors(s, &k))
				return (1);
			if (k != 2)
				return (1);
			k = 0;
			tmp = ft_split(s, ',');
			j = -1;
			while (tmp[++j])
				if (atoi(tmp[j]) > 255 || atoi(tmp[j]) < 0)
					return (1);
			if (j != 3)
				return (1);
		}
		i++;
	}
	return (0);
}
