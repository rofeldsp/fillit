#include <stdio.h> // delete later
#include "fillit.h"
#include <time.h> // убрать

unsigned long long int     ftpow(unsigned long long int number, int power)
{
	int     cache[power + 1];
	unsigned long long     i;

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

int 	checkmap(int *map, int sqrsize, int tetrnum, node *cell) {
	if (tetrnum > sqrsize) // проверяем, что текущий ряд входит в карту
		return (0);
	if ((map[tetrnum] | cell->tetromap[tetrnum]) == (map[tetrnum] ^ cell->tetromap[tetrnum])) // проверяем, что первый ряд тетроминошки влезает
	{
		if (checkmap(map, sqrsize, tetrnum + 1, cell) >= 0) // рекурсивно проверяем след ряд
			map[tetrnum] = map[tetrnum] | cell->tetromap[tetrnum]; // если все ок, то заполняем карту нашей фигурой
		else
			return (-1); // вот тут надо возвращаться и двигать фигуру, а потом уже если не найдено решение возврашать 0
	}
	else
		return (-1);
	return (1);
}

int     linebreak(node *cell, int sqrsize, int tetrnum)
{
	if (tetrnum > sqrsize) // проверяем, что текущий ряд входит в карту
		return (0);
	if (cell->tetromap[tetrnum] & ftpow(2, 16 - sqrsize))
	{
		cell->tetromap[tetrnum] >> 1;
		if ((linebreak(cell, map, sqrsize, tetrnum + 1)) > 0)
			cell->tetromap[tetrnum + 1] | 32768;
	}
	return (1);
}

int main() {
	unsigned long long int a;
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	a = 1737;
	printf("%llu\n", ftpow(a, 245));
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("time %f\n", cpu_time_used);
	return (0);
}