#include <stdio.h> // delete later
#include "fillit.h"
#include <time.h> // убрать

uint64_t     ftpow(uint64_t number, int power, node *tetr)
{
//	uint64_t     *cache;
//	int     i;

//	cache = (uint64_t *)malloc(sizeof(uint64_t) * 64);
//	cache[2] = number * number;
	if (power == 2)
		return (number * number);
	else if (power == 1)
		return (number);
	else if (power == 0)
		return (1);
	return (number = number * tetr->power[power - 1]);
//	i = 3;
//	while (i <= power)
//	{
//		number = number * tetr->power(i - 1);
//		cache[i] = cache[i - 1] * number;
//		i++;
//	}
//	number = cache[power];
//	free (cache);
//	return (number);
}

int	ft_sqrt_round(int nb)
{
	int a;

	a = 1;
	if (nb > 2147483647)
		return (0);
	while (a * a < nb)
		a++;
	return (a);
}
/*
int 	clearnumber(int sqrsize, node *tetr)
{
	int num;
	int power;

	power = 14;
	num = 32768;
	if (sqrsize == 2)
		num = 49152;
	else if (sqrsize == 3)
		num = 57344;
	else if (sqrsize == 4)
		num = 61440;
	else
	{
		while (sqrsize > 3) {
			num = num * tetr->power[power] * tetr->power[power - 1] *
				  tetr->power[power - 2] * tetr->power[power - 3];
			power -= 4;
			sqrsize -= 4;
		}
		if (sqrsize == 1)
			num = num * tetr->power[power - 1];
		if (sqrsize == 2)
			num = num * tetr->power[power - 1] * tetr->power[power - 2];
		if (sqrsize == 3)
			num = num * tetr->power[power - 1] * tetr->power[power - 2] *
					tetr->power[power - 3];
	}
	return (num);
}
int 	linebreak2(node *tetr, int tetrline, int sqrsize)
{
	unsigned short		cell1;
	unsigned short	 	cell2;
	unsigned short		cell3;
	unsigned short	 	cell4;

	if (tetr->tetromap[sqrsize - 1] != 0)
		return (-1);
	cell1 = 0;
	cell2 = 0;
	cell3 = 0;
	cell4 = 0;
	if ((tetr->tetromap[tetrline] & tetr->power[19 - sqrsize]) ==
	tetr->power[19 - sqrsize])
		cell1 = tetr->power[19 - sqrsize];
	if ((tetr->tetromap[tetrline] & tetr->power[18 - sqrsize]) ==
		tetr->power[18 - sqrsize])
		cell2 = tetr->power[18 - sqrsize];
	if ((tetr->tetromap[tetrline] & tetr->power[17 - sqrsize]) ==
		tetr->power[17 - sqrsize])
		cell3 = tetr->power[17 - sqrsize];
	if ((tetr->tetromap[tetrline] & tetr->power[16 - sqrsize]) ==
		tetr->power[16 - sqrsize])
		cell4 = tetr->power[16 - sqrsize];
	if (tetrline == sqrsize - 1)
		return (tetr->tetromap[tetrline] != 0 ? -1 : 0);
	tetr->tetromap[tetrline] >>= tetr->width;
	tetr->tetromap[tetrline] &= clearnumber(sqrsize, tetr);
	if (linebreak2(tetr, tetrline + 1, sqrsize) < 0)
		return (-1);
	tetr->tetromap[tetrline + 1] |= ((cell1 + cell2 + cell3 + cell4) <<
			(sqrsize - tetr->width));
	return (1);
}
*/
int 	linebreak(node *tetr, int sqrsize)
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

int 	move(node *tetr, int sqrsize)
{
	int		ret;

	if ((ret = linebreak(tetr, sqrsize)) != 0)
		return (ret);
	tetr->tetromap >>= 1;
	return (1);
}

int		checkmap(uint16_t *map, int sqrsize, node *tetr)
{
	while (1)
	{
		if ((*(uint64_t *)(map + 12 - tetr->line) & tetr->tetromap) == 0)
		{
			*(uint64_t *)(map + 12 - tetr->line) |= tetr->tetromap; //
			// будет ли это
			// значение возвращаться в функцию?
			return (1);
		} else if (move(tetr, sqrsize) < 0)
			return (-1);
	}
}

int 	moveprevnode(uint16_t *map, int sqrsize, node *tetr)
{
	if (tetr->prev == NULL)
		return (-1);
	tetr = tetr->prev;
	*(uint64_t *)(map + 12 - tetr->line) ^= tetr->tetromap;
	if (move (tetr, sqrsize) < 0)
		return (-1);
	return (1);
}

int 	fillmap(uint16_t *map, int sqrsize, node *tetr)
{
	while (1)
	{
		if (checkmap(map, sqrsize, tetr) == -1)
		{
			while (1)
				if (moveprevnode(map, sqrsize, tetr) == -1)
				{
					tetr->tetromap = tetr->buff;
					tetr->line = 0;
					if (tetr->prev == NULL)
						return (-1);
					tetr = tetr->prev;
				}
				else
				{
					if (tetr->prev == NULL)
						return (-1);
					tetr->tetromap = tetr->buff;
					tetr->line = 0;
					if (tetr->prev->prev == NULL)
						return (fillmap(map, sqrsize, tetr = tetr->prev));
					tetr = tetr->prev->prev;
					break;
				}
		}
		if (tetr->next == NULL)
			return (1);
		tetr = tetr->next;
	}
}

uint16_t	*create_map(void)
{
	int				i;
	uint16_t 		*map;

	i = 0;
	map = (uint16_t *)malloc(sizeof(uint16_t) * 16);
	while (i < 16)
		map[i++] = 0;
	return (map);
}

int 	deploy(node *tetr, int tetramount)
{
	uint16_t		*map;
	int 			sqrsize;
	int 			tetrline;

	tetrline = 0;
	sqrsize = ft_sqrt_round(4 * tetramount);
	while (1)
	{
		map = create_map();
		if (fillmap(map, sqrsize, tetr) == -1)
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

int 	checkheight(node *tetr)
{
	int		i;

	i = 0;
	if ((tetr->tetromap & tetr->power[59]) != 0)
		return (1);
	if ((tetr->tetromap & 3221225472) != 0)
		return (3);
	if ((tetr->tetromap & 32768) != 0)
		return (4);
	else
		return (2);
}

char		*map_to_print(int sqrsize)
{
	int		i;
	int		j;
	char 	*map;

	map = (char*)malloc(sizeof(char) * (sqrsize + 1) * sqrsize);
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
	return (map);
}

char 	*fillfigure(char *map, node *tetr, int sqrsize, char letter)
{
	int 		i;
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

node	*addnode(unsigned short *t, node *head, int a)
{
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL);
	i = 0;
//	tetr->power = (unsigned short *)malloc(sizeof(short) * 16);
	while (i < 64)
	{
		tetr->power[i] = ftpow(2, i, tetr);
		i++;
	}
	tetr->tetromap = ((((*(uint64_t *)(t + a)) & 61440) << 48) + (((*(uint64_t*)
		(t + a)) & 3840) << 36) + (((*(uint64_t *)(t + a)) & 240) << 24) +
		(((*(uint64_t *)(t + a)) & 15) >> 12));
	tetr->prev = head;
	tetr->next = NULL;
	tetr->line = 0;
	tetr->height = checkheight(tetr);
	tetr->buff = tetr->tetromap;
	return (tetr);
}

node	*createstruct(unsigned short *t, int tetramount)
{
	int		tetrnum;
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL); //обработать ошибку
	tetr->tetromap = ((((*(uint64_t *)t) & 61440) << 48) + (((*(uint64_t *)t)
		& 3840) << 36) + (((*(uint64_t *)t) & 240) << 24) + (((*(uint64_t *)t) &
		15) >> 12));
	tetr->prev = NULL;
	tetr->next = NULL;
	tetr->line = 0;
//	tetr->power = (unsigned short *)malloc(sizeof(short) * 16);
	while (i < 64)
	{
		tetr->power[i] = ftpow(2, i, tetr);
		i++;
	}
	tetr->height = checkheight(tetr);
	tetr->buff = tetr->tetromap;
	tetrnum = 1;
	while (tetrnum < tetramount)
	{
		tetr->next = addnode(t, tetr, tetrnum);
		tetr = tetr->next;
		tetrnum++;
	}
	while (tetr->prev != NULL)
		tetr = tetr->prev;
	return (tetr);
}

int main()
{
	int 	i;
	clock_t	start, end;
	double 	cpu_time_used;
	char 	*map;
	uint16_t	*tetro;
	int		sqrsize;
	node	*tetr;
	char 	letter;
	int		tetramount;

	tetramount = 12;
	tetro = (unsigned short *)malloc(sizeof(short) * tetramount);
	tetro[0] = 52224;
	tetro[1] = 35968;
	tetro[2] = 27648;
	tetro[3] = 52224;
	tetro[4] = 19584;
	tetro[5] = 57856;
	tetro[6] = 50240;
	tetro[7] = 52224;
	tetro[8] = 27648;
	tetro[9] = 50240;
	tetro[10] = 35904;
	tetro[11] = 58368;
//	tetro[12] = 58368;
//	tetro[0] = 52224;
//	tetro[1] = 57856;
//	tetro[2] = 35008;
//	tetro[3] = 50688;
//	tetro[4] = 19520;
//	tetro[5] = 35968;
//	tetro[6] = 50688;
//	tetro[7] = 52224;
//	tetro[8] = 57856;
//	tetro[9] = 61440;
//	tetro[10] = 57856;
//	tetro[11] = 50240;
//	tetro[12] = 50688;
//	tetro[13] = 61440;
//	tetro[14] = 35008;
//	tetro[15] = 50688;
	letter = 65;
	start = clock();
	tetr = createstruct(tetro, tetramount);
	sqrsize = deploy(tetr, tetramount);
	map = map_to_print(sqrsize);
	i = 0;
	while (i++ < tetramount)
	{
		map = fillfigure(map, tetr, sqrsize, letter);
		letter++;
		tetr = tetr->next;
	}
	ft_putstr(map);
	free(map);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("time %f\n", cpu_time_used);
	return (0);
}