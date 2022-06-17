
#include "cub3d.h"

char	**map_filling(int fd)
{
	int c;
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
	free(s);
	return (map);
}