/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:42:02 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/25 18:49:02 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

typedef struct textter
{
	char *so;
	char *we;
	char *ea;
	char *no;
}t_textter;

typedef struct s_colors
{
	int	f[3];
	int c[3];
}t_colors;

typedef struct s_rend {
	char	**map;
	void	*mlx;
	void	*mlx_win;
	char	player;
	void	*wall;
	void	*empty;
	void	*spaces;
	void	*p;
	void	*floor;
	t_colors *colors;
	t_textter *textter;
	int		width;
	int		height;
	int		i;
	int		j;
}	t_rend;

void	ft_error(void);
size_t	ft_strlen(const char *s);
void	check_extension(char *av);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const	char *s);
char	*ft_strjoin(char *s1, char *s2);
char	**map_filling(int fd);
int		map_final_check(char **map,t_rend *game);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		check_colors(char **six_lines, int i, int k, int j);
int		check_first_sixlines(char *s);
int		check_textur(char **six_lines);
int		check_duble_element(char **six_lines);
int		ft_check_new_line(char **map, char *s);
int		map_parsing(char **six_lines, char **map,t_rend *game);

int	image_rendering(t_rend *game);
void	mlx_start(char **map,t_rend *game);

int	take_key(int key, t_rend *m);
#endif
