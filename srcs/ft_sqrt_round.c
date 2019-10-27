/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_round.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 12:36:46 by rofeldsp          #+#    #+#             */
/*   Updated: 2019/10/27 12:36:46 by rofeldsp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fillit.h"
#include "../includes/fillit.h"

int				ft_sqrt_round(int nb)
{
	int a;

	a = 1;
	if (nb > 2147483647)
		return (0);
	while (a * a < nb)
		a++;
	return (a);
}
