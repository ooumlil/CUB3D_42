/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:33:14 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/21 22:32:57 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**ft_free(char *s, char **map)
{
	int	i;

	i = 0;
	if (s)
		free(s);
	while (map[i])
		free(map[i++]);
	free(map);
	return (NULL);
}

char	**map_filling(int fd)
{
	int		c;
	char	*buf;
	char	*s;
	char	**map;

	buf = (char *)malloc(sizeof(char) * (2));
	if (!buf)
		return (NULL);
	c = 1;
	while (c > 0)
	{
		c = read(fd, buf, 1);
		if (c == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[c] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	map = ft_split(s, '\n');
	if (ft_check_new_line(map, s))
		return (ft_free(s, map));
	return (free(s), map);
}
