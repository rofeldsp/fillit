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

int 	move(node *cell, int tetrnum, int sqrsize)
{

}

int 	checkmap(int *map, int sqrsize, int tetrnum, node *cell) {
	if (tetrnum > sqrsize) // проверяем, что текущий ряд входит в карту
		return (0);
	if ((map[tetrnum] | cell->tetromap[tetrnum]) == (map[tetrnum] ^ cell->tetromap[tetrnum])) // проверяем, что первый ряд тетроминошки влезает
	{
		if (checkmap(map, sqrsize, tetrnum + 1, cell) >= 0) // рекурсивно проверяем след ряд
			map[tetrnum] = map[tetrnum] | cell->tetromap[tetrnum]; // если все ок, то заполняем карту нашей фигурой
		else if (move(cell, tetrnum, sqrsize) > 0)
			if (checkmap(map, sqrsize, tetrnum, cell) >= 0)
				return (1);
		else
			return (-1); // вот тут надо возвращаться и двигать фигуру, а потом уже если не найдено решение возврашать 0
	}
	else
		return (-1); // we should mpve the block here too.
	return (1);
}

int 	linebreaktwoways(node *cell, int tetrnum, int sqrsize)
{
	if (tetrnum + 2 > sqrsize)
		return (0);
	cell->tetromap[tetrnum] >>= 2;
	cell->tetromap[tetrnum - 1] >>= 2;
	cell->tetromap[tetrnum + 1] >>= 2;
	cell->tetromap[tetrnum + 1] = cell->tetromap[tetrnum + 1] | 49152;
	cell->tetromap[tetrnum] = cell->tetromap[tetrnum + 1] | 32768;
	cell->tetromap[tetrnum + 2] = cell->tetromap[tetrnum + 1] | 32768;
	return (1);
}

int		linebreakreverse(node *cell, int tetrnum, int sqrsize)
{
	int		tetrlength;
	int 	tetrheight;

	tetrlength = 2;
	tetrheight = 1;
	if (cell->tetromap[tetrnum] &= ftpow(2, 16 - sqrsize + 2))
		tetrlength = 3;
	if (cell->tetromap[tetrnum - 2] != 0)
		tetrheight = 2;
	cell->tetromap[tetrnum] >>= tetrlength;
	cell->



}

int     linebreak(node *cell, int sqrsize, int tetrnum, int flag)
{
	if (tetrnum > sqrsize)
		return (0);
	if (cell->tetromap[tetrnum] &= ftpow(2, 16 - sqrsize))
	{
		if ((cell->tetromap[tetrnum + 1] == 0) && flag == 0 &&
		cell->tetromap[tetrnum - 1] != 0)
			linebreakreverse
		if ((cell->tetromap[tetrnum + 1] != 0) && flag == 0 &&
				(cell->tetromap[tetrnum - 1] != 0))
			if (linebreaktwoways(cell, tetrnum, sqrsize) > 0)
				return (1);
			else
				return (0);
		if (tetrnum == sqrsize)
			return (-1);
		else
		{
			cell->tetromap[tetrnum] >>= 1; // решить вопрос с переносом
			// фигуру, где переносить надо не один раз
			if ((cell->tetromap[tetrnum + 1] | 0) != 0)
				if (linebreak(cell, sqrsize, tetrnum + 1, flag = 1) > 0)
					cell->tetromap[tetrnum + 1] = cell->tetromap[tetrnum + 1] |
					32768;
				else
					return (-1);
			else
				cell->tetromap[tetrnum + 1] = cell->tetromap[tetrnum + 1] |
						32768;
			return (1);
		}
	}
	else if (flag > 0)
		cell->tetromap[tetrnum] >>= 1;
	linebreak(cell, sqrsize, tetrnum + 1, flag);
	return (1);
}
/*
int     linebreak(node *cell, int sqrsize, int tetrnum)
{
	int		ret;

	if (tetrnum > sqrsize) // проверяем, что текущий ряд входит в карту
		return (0);
	if (cell->tetromap[tetrnum] & ftpow(2, 16 - sqrsize) == ftpow(2, 16 - sqrsize))
	{
		if ((ret = (linebreak(cell, sqrsize, tetrnum + 1))) > 0)
		{
			cell->tetromap[tetrnum] >> 1;
			if ((cell->tetromap[tetrnum + 1] | 0) != 0)
				cell->tetromap[tetrnum + 1] | 32768;
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