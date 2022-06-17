
#include "cub3d.h"

void ft_check_map(fd)
{
	int i;
	int j;
	char **map;
	int fd;
	char *buf;
	buf = (char *)malloc(sizeof(char) * (2));
	if (!buf)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buf, 1);
		if (i == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = '\0';
		m = ft_strjoin(m, buf);
	}
	free(buf);
	map = ft_split(s, '\n');
	free(s);
	
}