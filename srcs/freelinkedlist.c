/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelinkedlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:36:30 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 12:36:30 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fillit.h"
#include "../includes/fillit.h"

void			freelist(node *tetr)
{
	node	*tmp;

	while (tetr != NULL)
	{
		tmp = tetr;
		tetr = tetr->prev;
		free(tmp);
	}
}
