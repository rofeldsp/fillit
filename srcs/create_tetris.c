/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tetris.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:36:37 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 16:51:38 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h" //

int				checkheight(node *tetr)
{
	int		i;

	i = 0;
	if ((tetr->tetromap & tetr->power[60]) != 0)
		return (1);
	if ((tetr->tetromap & 32768) != 0)
		return (4);
	if ((tetr->tetromap & 3221225472) != 0)
		return (3);
	else
		return (2);
}

int				checkwidth(node *tetr)
{
	int		i;

	i = 0;
	if ((tetr->tetromap & tetr->power[60]) != 0)
		return (4);
	if ((tetr->tetromap & 32768) != 0)
		return (1);
	if ((tetr->tetromap & 3221225472) != 0)
		return (2);
	else
		return (3);
}

node			*addnode(uint64_t *t, node *head, int tetrnum)
{
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL);
	i = 0;
	while (i < 64)
	{
		tetr->power[i] = ftpow(2, i, tetr);
		i++;
	}
	tetr->tetromap = (((t[tetrnum] & 61440) << 48) + ((t[tetrnum] & 3840) << 36)
			+ ((t[tetrnum] & 240) << 24) + ((t[tetrnum] & 15) << 12));
	tetr->prev = head;
	tetr->next = NULL;
	tetr->line = 0;
	tetr->height = checkheight(tetr);
	tetr->width = checkwidth(tetr);
	tetr->buff = tetr->tetromap;
	return (tetr);
}

node			*createstruct(uint64_t *t, int tetramount)
{
	int		tetrnum;
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL);
	tetr->tetromap = (((t[0] & 61440) << 48) + ((t[0] & 3840) << 36) +
							((t[0] & 240) << 24) + ((t[0] & 15) << 12));
	tetr->prev = NULL;
	tetr->next = NULL;
	tetr->line = 0;
	i = 0;
	while (i < 64)
	{
		tetr->power[i] = ftpow(2, i, tetr);
		i++;
	}
	tetr->height = checkheight(tetr);
	tetr->width = checkwidth(tetr);
	tetr->buff = tetr->tetromap;
	tetrnum = 1;
	while (tetrnum < tetramount)
	{
		if (!(tetr->next = addnode(t, tetr, tetrnum)))
			return (NULL);
		tetr = tetr->next;
		tetrnum++;
	}
	while (tetr->prev != NULL)
		tetr = tetr->prev;
	return (tetr);
}
