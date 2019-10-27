/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:34:50 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 12:34:50 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

node			*move_to_start(node *tetr)
{
	tetr->tetromap = tetr->buff;
	tetr->line = 0;
	if (tetr->prev == NULL)
		return (NULL);
	tetr = tetr->prev;
	return (tetr);
}

int				fill_map(uint16_t *map, int sqrsize, node *tetr)
{
	while (1)
	{
		if (checkmap(map, sqrsize, tetr) == -1)
		{
			while (1)
				if (moveprevnode(map, sqrsize, tetr) == -1)
				{
					if (!(tetr = move_to_start(tetr)))
						return (-1);
				}
				else
				{
					if (!(tetr = move_to_start(tetr)))
						return (-1);
					if (tetr->prev == NULL)
						return (fill_map(map, sqrsize, tetr = tetr));
					tetr = tetr->prev;
					break ;
				}
		}
		if (tetr->next == NULL)
			return (1);
		tetr = tetr->next;
	}
}

uint16_t		*create_map(void)
{
	int				i;
	uint16_t		*map;

	i = 0;
	if (!(map = (uint16_t *)malloc(sizeof(uint16_t) * 16)))
		return (NULL);
	while (i < 16)
		map[i++] = 0;
	return (map);
}

node			*move_tetrs_back(node *tetr)
{
	while (tetr->next != NULL)
	{
		tetr->tetromap = tetr->buff;
		tetr->line = 0;
		tetr = tetr->next;
	}
	tetr->tetromap = tetr->buff;
	tetr->line = 0;
	while (tetr->prev != NULL)
		tetr = tetr->prev;
	return (tetr);
}

int				deploy(node *tetr, int tetramount)
{
	uint16_t		*map;
	int				sqrsize;

	sqrsize = ft_sqrt_round(4 * tetramount);
	while (1)
	{
		if (!(map = create_map()))
			return (0);
		if (fill_map(map, sqrsize, tetr) == -1)
		{
			tetr = move_tetrs_back(tetr);
			sqrsize++;
			free(map);
		}
		else
		{
			free(map);
			return (sqrsize);
		}
	}
}
