/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tetris.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:36:51 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 12:37:06 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fillit.h"
#include "../includes/fillit.h"

char			*map_to_print(int sqrsize)
{
	int		i;
	int		j;
	char	*map;

	map = (char*)malloc(sizeof(char) * ((sqrsize + 1) * sqrsize + 1));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < ((sqrsize + 1) * sqrsize))
	{
		j = -1;
		while (++j < sqrsize)
			map[i + j] = '.';
		map[i + j] = '\n';
		i += (sqrsize + 1);
	}
	map[i] = '\0';
	return (map);
}

char			*fillfigure(char *map, node *tetr, int sqrsize, char letter)
{
	int			i;
	int			j;
	int			a;

	i = 0;
	a = 0;
	while (i <= (sqrsize + 1) * (sqrsize - 1))
	{
		j = 0;
		while (j < sqrsize)
		{
			if (a >= tetr->line && a - tetr->line < 4)
				if ((tetr->tetromap & tetr->power[(63 - 16 * (a -
										tetr->line) - j)]) != 0)
					map[i + j] = letter;
			j++;
		}
		a++;
		i += (sqrsize + 1);
	}
	return (map);
}
