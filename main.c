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

int	ft_sqrt(int nb)
{
	int a;

	a = 1;
	if (nb > 2147483647)
		return (0);
	while (a < nb / 2)
	{
		if (a * a == nb)
			return (a);
		a++;
	}
	return (0);
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

int 	checkmap(unsigned short *map, int sqrsize, int tetrline, node *tetr) {
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

void	clearmap(unsigned short *map, int sqrsize, int tetrline, node *tetr)
{
	while (tetrline < sqrsize)
	{
		map[tetrline] ^= tetr->tetromap[tetrline];
		tetrline++;
	}
}

int 	moveprevnode(unsigned short *map, int sqrsize, int tetrline, node *tetr)
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

int 	fillmap(unsigned short *map, int sqrsize, int tetrline, node *tetr)
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
	unsigned short	*map;
	int				i;

	map = (unsigned short *)malloc(sizeof(short) * 16);
	i = 0;
	while (i < 16)
		map[i++] = 0;
	return (map);
}

int 	deploy(node *tetr, int tetramount, int tetrline)
{
	unsigned short	*map;
	int 			sqrsize;

	sqrsize = ft_sqrt(4 * tetramount);
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

node	*addnode(unsigned short *tetromino, node *head, int tetrnum)
{
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL); // обработать ошибку
	tetr->tetromap = (unsigned short *)malloc(sizeof(short) * 16);
	tetr->prev = head;
	tetr->next = NULL;
	tetr->tetromap[0] = (tetromino[tetrnum] & 61440);
	tetr->tetromap[1] = (tetromino[tetrnum] & 3840) << 4;
	tetr->tetromap[2] = (tetromino[tetrnum] & 240) << 8;
	tetr->tetromap[3] = (tetromino[tetrnum] & 15) << 12;
	i = 3;
	while (++i < 16)
		tetr->tetromap[i] = 0;
	tetr->width = checkwidth(tetr);
	return (tetr);
}

node	*createstruct(unsigned short *tetromino)
{
	int		tetrnum;
	node	*tetr;
	int		i;

	tetr = (node*)malloc(sizeof(node));
	if (tetr == NULL)
		return (NULL); //обработать ошибку
	tetr->tetromap = (unsigned short *)malloc(sizeof(short) * 16);
	tetr->prev = NULL;
	tetr->next = NULL;
	tetr->tetromap[0] = (tetromino[0] & 61440);
	tetr->tetromap[1] = (tetromino[0] & 3840) << 4;
	tetr->tetromap[2] = (tetromino[0] & 240) << 8;
	tetr->tetromap[3] = ((tetromino[0] & 15) << 12);
	i = 3;
	while (++i < 16)
		tetr->tetromap[i] = 0;
	tetr->width = checkwidth(tetr);
	tetrnum = 1;
	while (tetromino[tetrnum])
	{
		tetr->next = addnode(tetromino, tetr, tetrnum);
		tetr = tetr->next;
		tetrnum++;
	}
	while (tetr->prev != NULL)
		tetr = tetr->prev;
	return (tetr);
}

char		*map_to_print(int sqrsize)
{
	int		i;
	int		j;
	char 	*map;

	map = (char*)malloc(sizeof(char) * (sqrsize + 1) * 4);
	if (map == NULL)
		return (NULL); // обработать в принимающей функции эту ошибку
	i = 0;
	while (i < ((sqrsize + 1) * 4))
	{
		j = -1;
		while (++j < sqrsize)
			map[i + j] = '0';
		map[i + j] = '\n'; // должна ли карта в конце иметь перенос?
		i += (sqrsize + 1);
	}
	return (map);
}

char 	*fillfigure(char *map, node *tetr, int sqrsize, char letter)
{
	int 		i;
	int			j;

	i = 0;
	while (i < (sqrsize + 1) * 4)
	{
		j = 0;
		while (j < sqrsize)
		{
			if ((tetr->tetromap[0] & ftpow(2, 16 - sqrsize + j)) != 0)
				map[i + j] = letter;
			j++;
		}
		i += (sqrsize + 1);
	}
	return (map);
}

int main()
{
	int 	i;
	clock_t start, end;
	double 	cpu_time_used;
	char 	*map;
	unsigned short	*tetro;
	int		sqrsize;
	node	*tetr;
	char 	letter;
	int		tetramount;

	tetramount = 4;
	tetro = (unsigned short *)malloc(sizeof(short) * tetramount);
	tetro[0] = 52224;
	tetro[1] = 35008;
	tetro[2] = 11776;
	tetro[3] = 34952;
	letter = 65;
	start = clock();
	tetr = createstruct(tetro);
	sqrsize = deploy(tetr, tetramount,0);
	map = map_to_print(sqrsize);
	i = 0;
	while (++i < tetramount)
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