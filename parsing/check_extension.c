/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooumlil <ooumlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:35:30 by ooumlil           #+#    #+#             */
/*   Updated: 2022/06/21 22:39:14 by ooumlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extension(char *av)
{
	size_t	i;

	i = ft_strlen(av);
	if (av[i - 1] == 'b' && av[i - 2] == 'u' \
		&& av[i - 3] == 'c' && av[i - 4] == '.')
		return ;
	else
	{
		write (2, "Error\nWrong Extension!\n", 23);
		exit (1);
	}
}
