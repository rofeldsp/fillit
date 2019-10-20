#include <stdio.h> // delete later
#include "fillit.h"
#include <time.h> // убрать

int     ftpow(int number, int power)
{
	int     cache[power + 1];
	int     i;

	cache[2] = number * number;
	i = 3;
	while (i <= power)
	{
		cache[i] = cache[i - 1] * number;
		i++;
	}
	number = cache[power];
	return (number);
}

int 	linebreak2(node *tetr, int tetrline, int sqrsize)
{
	int		cell1;
	int 	cell2;
	int		cell3;
	int 	cell4;

	cell1 = 0;
	cell2 = 0;
	cell3 = 0;
	cell4 = 0;
	if ((tetr->tetromap[tetrline] & ftpow(2, 19 - sqrsize)) == ftpow(2, 19
																		- sqrsize))
		cell1 = 4096;
	if ((tetr->tetromap[tetrline] & ftpow(2, 18 - sqrsize)) == ftpow(2, 18 -
																		sqrsize))
		cell2 = 8192;
	if ((tetr->tetromap[tetrline] & ftpow(2, 17 - sqrsize)) == ftpow(2, 17 -
																		sqrsize))
		cell3 = 16384;
	if ((tetr->tetromap[tetrline] & ftpow(2, 16 - sqrsize)) == ftpow(2, 16 -
																		sqrsize))
		cell4 = 32768;
	if (tetrline == sqrsize - 1)
		return (tetr->tetromap[tetrline] != 0 ? -1 : 0);
	tetr->tetromap[tetrline] >>= tetr->width;
	if (linebreak2(tetr, tetrline + 1, sqrsize) < 0)
		return (-1);
	tetr->tetromap[tetrline + 1] |= (cell1 + cell2 + cell3 + cell4);
	return (1);
}

int 	linebreak(node *tetr, int sqrsize)
{
	int tetrline;

	tetrline = 0;
	while (tetrline < sqrsize) {
		if ((tetr->tetromap[tetrline] & ftpow(2, 16 - sqrsize)) == ftpow(2,
																		 16 - sqrsize))
			return (linebreak2(tetr, tetrline = 0, sqrsize) == -1 ? -1 : 1);
		tetrline++;
	}
	return (0);
}

int 	move(node *tetr, int tetrline, int sqrsize)
{
	int		ret;

	if ((ret = linebreak(tetr, sqrsize)) != 0)
		return (ret);
	while (tetrline < sqrsize)
	{
		tetr->tetromap[tetrline] >>= 1;
		tetrline++;
	}
	return (1);
}

int 	checkmap(unsigned int *map, int sqrsize, int tetrline, node *tetr) {
	while (1)
	{
		if (tetrline == sqrsize) // проверяем, что текущий ряд входит в карту
			return (0);
		if ((map[tetrline] | tetr->tetromap[tetrline]) == (map[tetrline] ^
		tetr->tetromap[tetrline])) // проверяем, что первый ряд тетроминошки влезает
		{
			if (checkmap(map, sqrsize, tetrline + 1, tetr) >=
				0) // рекурсивно проверяем след строку
				map[tetrline] |= tetr->tetromap[tetrline]; // если все ок, то
				// заполняем карту нашей фигурой
			else if (move(tetr, tetrline, sqrsize) > 0)
				if (checkmap(map, sqrsize, tetrline, tetr) >= 0)
					map[tetrline] |= tetr->tetromap[tetrline]; // если все ок, то
				else
					return (-1);
			else
				return (-1);
		}
		else if (move(tetr, tetrline, sqrsize) > 0)
			if (checkmap(map, sqrsize, tetrline, tetr) >= 0)
				map[tetrline] |= tetr->tetromap[tetrline]; // если все ок, то
			else
				return (-1);
		else
			return (-1);
		return (1);
	}
}

void	clearmap(unsigned int *map, int sqrsize, int tetrline, node *tetr)
{
	while (tetrline < sqrsize)
	{
		map[tetrline] ^= tetr->tetromap[tetrline];
		tetrline++;
	}
}

int 	moveprevnode(unsigned int *map, int sqrsize, int tetrline, node *tetr)
{
	clearmap(map, sqrsize, tetrline, tetr = tetr->prev);
	if (move (tetr, tetrline, sqrsize) < 0)
		return (-1);
	return (1);
}

void	movetostart(node *tetr, int sqrsize, int tetrline)
{
	int		buff;

	while (tetr->tetromap[tetrline == 0])
		tetrline++;
	buff = tetrline;
	while (tetr->tetromap[buff] != 0 || buff != sqrsize)
	{
		tetr->tetromap[buff - tetrline] = tetr->tetromap[buff];
		buff++;
	}
	while (1)
	{
		tetrline = -1;
		while (++tetrline < sqrsize)
			if ((tetr->tetromap[tetrline] & 32786) == 32786)
				return ;
		tetrline = -1;
		while (++tetrline < sqrsize) // проверить, что начинаем с нуля здесь
			tetr->tetromap[tetrline] <<= 1;
	}
}

int 	fillmap(unsigned int *map, int sqrsize, int tetrline, node *tetr)
{
	while (1)
	{
		if (checkmap(map, sqrsize, tetrline, tetr) == -1)
		{
			while (1)
				if (moveprevnode(map, sqrsize, tetrline, tetr) == -1)
				{
					movetostart(tetr, sqrsize, tetrline);
					tetr = tetr->prev;
				}
				else
				{
					if (tetr->next == NULL)
						return (-1);
					movetostart(tetr, sqrsize, tetrline);
					tetr = tetr->prev->prev;
					break ;
				}
		}
		if (tetr->next == NULL)
			return (1);
		tetr = tetr->next;
	}
}

unsigned short	*create_map(void)
{
	unsigned short	map[16];
	int				i;

	i = 0;
	while (i < 16)
		map[i++] = 0;
}

int 	deploy(node *tetr, int tetramount, int tetrline)
{
	unsigned short	*map;
	int 			sqrsize;

	sqrsize = 4 * tetramount;
	map = create_map();
	while (1)
	{
		if (fillmap(map, sqrsize, tetrline, tetr) == -1)
		{
			while (tetr->next != NULL) // можно ли так написать, или надо
				// tetr->next не равно нулю и после цикла еще одна итерация
			{
				movetostart(tetr, sqrsize, tetrline);
				tetr = tetr->next;
			}
			movetostart(tetr, sqrsize, tetrline);
			while (tetr->prev != NULL)
				tetr = tetr->prev;
			sqrsize++;
		}
		else
			return (sqrsize);
	}
}

int 	checkwidth(node *tetr)
{
	int		i;

	i = 0;
	if ((tetr->tetromap[0] & 4096) == 4096)
		return (4);
	while (i < 4)
	{
		if (tetr->tetromap[i] & 8192)
			return (3);
		i++;
	}
	if ((tetr->tetromap[3] & 32768) == 32768)
		return (1);
	else
		return (2);
}

node	*addnode(unsigned int tetromino, node **head, int tetrnum)
{
	node	*tetr;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL); // обработать ошибку
	tetr->tetromap = (unsigned int *)malloc(sizeof(short) * 16);
	tetr->prev = *head;
	tetr->next = NULL;
	tetr->tetromap[0] = tetromino[tetrnum] & 61440;
	tetr->tetromap[1] = (tetromino[tetrnum] & 3840) << 4;
	tetr->tetromap[2] = (tetromino[tetrnum] & 240) << 8;
	tetr->tetromap[3] = (tetromino[tetrnum] & 15) << 12;
	tetr->width = checkwidth(tetr);
	return (tetr);
}

node	*creatstruct(unsigned int *tetromino)
{
	int		tetrnum;
	node	*tetr;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL); //обработать ошибку
	tetr->tetromap = (unsigned int *)malloc(sizeof(short) * 16);
	tetr->prev = NULL;
	tetr->next = NULL;
	tetr->tetromap[0] = (tetromino[0] & 61440);
	tetr->tetromap[3] = ((tetromino[0] & 15) << 12);
	tetr->width = checkwidth(tetr);
	tetrnum = 1;
	while (tetromino[tetrnum])
	{
		tetr->next = addnode(tetromino, tetr, tetrnum);
		tetr = tetr->next;
	}
	while (tetr->prev != NULL)
		tetr = tetr->prev;
	return (tetr);
}

char 	*printfigure(node *tetr, int sqrsize, char letter)
{
	char		*map; // надо создать отдельную функцию создания карты, ее
	// вызывать в мейне, а потом уже в цикле вызывать эту функцию.
	int 		i;
	int			j;

	i = 0;
	map = (char*)malloc(sizeof(char) * (sqrsize + 1) * 4);
	if (map == NULL)
		return (0); // обрабать ошибку
	while (i < (sqrsize + 1) * 4)
	{
		j = 0;
		while (j < sqrsize)
		{
			if ((tetr->tetromap[0] & ftpow(2, 16 - sqrsize + j)) != 0)
				map[i + j] = letter;
			else
				map[i + j] = '0';
			j++;
		}
		map[i + j] = '\n';
		i += (sqrsize + 1);
	}
	return (map);
}
/*
int 	linebreaktwoways(node *cell, int tetrline, int sqrsize)
{
	if (tetrline + 2 > sqrsize)
		return (0);
	cell->tetromap[tetrline] >>= 2;
	cell->tetromap[tetrline - 1] >>= 2;
	cell->tetromap[tetrline + 1] >>= 2;
	cell->tetromap[tetrline + 1] = cell->tetromap[tetrline + 1] | 49152;
	cell->tetromap[tetrline] = cell->tetromap[tetrline + 1] | 32768;
	cell->tetromap[tetrline + 2] = cell->tetromap[tetrline + 1] | 32768;
	return (1);
}

int		linebreakreverse(node *cell, int tetrline, int sqrsize)
{
	int		tetrlength;
	int 	tetrheight;

	tetrlength = 2;
	tetrheight = 1;
	if (cell->tetromap[tetrline] &= ftpow(2, 16 - sqrsize + 2))
		tetrlength = 3;
	if (cell->tetromap[tetrline - 2] != 0)
		tetrheight = 2;
	cell->tetromap[tetrline] >>= tetrlength;
	cell->



}

int     linebreak(node *cell, int sqrsize, int tetrline, int flag)
{
	if (tetrline > sqrsize)
		return (0);
	if (cell->tetromap[tetrline] &= ftpow(2, 16 - sqrsize)) // не сработает,
		// тут присвоение идет
	{
		if ((cell->tetromap[tetrline + 1] == 0) && flag == 0 &&
		cell->tetromap[tetrline - 1] != 0)
			linebreakreverse
		if ((cell->tetromap[tetrline + 1] != 0) && flag == 0 &&
				(cell->tetromap[tetrline - 1] != 0))
			if (linebreaktwoways(cell, tetrline, sqrsize) > 0)
				return (1);
			else
				return (0);
		if (tetrline == sqrsize)
			return (-1);
		else
		{
			cell->tetromap[tetrline] >>= 1; // решить вопрос с переносом
			// фигуру, где переносить надо не один раз
			if ((cell->tetromap[tetrline + 1] | 0) != 0)
				if (linebreak(cell, sqrsize, tetrline + 1, flag = 1) > 0)
					cell->tetromap[tetrline + 1] = cell->tetromap[tetrline + 1] |
					32768;
				else
					return (-1);
			else
				cell->tetromap[tetrline + 1] = cell->tetromap[tetrline + 1] |
						32768;
			return (1);
		}
	}
	else if (flag > 0)
		cell->tetromap[tetrline] >>= 1;
	linebreak(cell, sqrsize, tetrline + 1, flag);
	return (1);
}

int     linebreak(node *cell, int sqrsize, int tetrline)
{
	int		ret;

	if (tetrline > sqrsize) // проверяем, что текущий ряд входит в карту
		return (0);
	if (cell->tetromap[tetrline] & ftpow(2, 16 - sqrsize) == ftpow(2, 16 - sqrsize))
	{
		if ((ret = (linebreak(cell, sqrsize, tetrline + 1))) > 0)
		{
			cell->tetromap[tetrline] >> 1;
			if ((cell->tetromap[tetrline + 1] | 0) != 0)
				cell->tetromap[tetrline + 1] | 32768;
		}
		else
			return (-1);
	}
	else
		return (2);
	return (1);
}
*/
int main()
{
	int a;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	a = 1737;
	printf("%d\n", ftpow(a, 245));
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("time %f\n", cpu_time_used);
	return (0);
}