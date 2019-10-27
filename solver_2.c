/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:36:17 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 12:37:06 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				linebreak(node *tetr, int sqrsize)
{
	if (((tetr->tetromap & tetr->power[64 - sqrsize]) != 0) || (
			(tetr->tetromap & tetr->power[48 - sqrsize]) != 0) || (
				(tetr->tetromap & tetr->power[32 - sqrsize]) != 0) || (
				(tetr->tetromap & tetr->power[16 - sqrsize]) != 0))
	{
		if (tetr->line == sqrsize - tetr->height)
			return (-1);
		tetr->line++;
		tetr->tetromap = tetr->buff;
	}
	else
		return (0);
	return (1);
}

int				move(node *tetr, int sqrsize)
{
	int ret;

	if ((ret = linebreak(tetr, sqrsize)) != 0)
		return (ret);
	tetr->tetromap >>= 1;
	return (1);
}

int				checkmap(uint16_t *map, int sqrsize, node *tetr)
{
	if (sqrsize < tetr->height || sqrsize < tetr->width)
		return (-1);
	while (1)
	{
		if ((*(uint64_t *)(map + 12 - tetr->line) & tetr->tetromap) == 0)
		{
			*(uint64_t *)(map + 12 - tetr->line) |= tetr->tetromap;
			return (1);
		}
		else if (move(tetr, sqrsize) < 0)
			return (-1);
	}
}

int				moveprevnode(uint16_t *map, int sqrsize, node *tetr)
{
	if (tetr->prev == NULL)
		return (-1);
	tetr = tetr->prev;
	*(uint64_t *)(map + 12 - tetr->line) ^= tetr->tetromap;
	if (move(tetr, sqrsize) < 0)
		return (-1);
	return (1);
}
