/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:33:14 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/19 22:45:23 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_check_new_line(char **map,char *s)
{	
	int i;
	int c;
	
	i  = 0;
	while(s[i])
	{
		if(s[i] == '\n'&& s[i + 1] == '1')
			break ;
		i++;
	}
	int j = i;
	c = 0;
	while (s[j])
	{
		if(s[j] == '\n')
			c++;
		j++;
	}
	j = 0;
	while(map[j])
		j++;
	if(j - 6 != c)
	{
		printf("invalid map\n");
		return (1);
	}
	return (0);
}
int	check_colors(char **six_lines)
{
	int		i;
	int		j;
	char	**tmp;
	char	*s;

	i = -1;
	while (six_lines[++i])
	{
		if (ft_strchr(six_lines[i], ','))
		{
			if (six_lines[i][ft_strlen(six_lines[i]) - 1] == ' ')
				return (1);
			s = ft_strchr(six_lines[i], ' ');
			++s;
			tmp = ft_split(s, ',');
			j = -1;
			while (tmp[++j])
				if (atoi(tmp[j]) > 255 || atoi(tmp[j]) < 0)
					return (1);
			if (j != 3)
				return (1);
		}
	}
	return (0);
}

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
	// if(ft_check_new_line(map,s))
	// {
	// 	free(s);
	// 	////free map
	// 	return (NULL);
	// }
	free(s);
	return (map);
}
