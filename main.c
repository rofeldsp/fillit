#include <stdio.h> // delete later
#include "fillit.h"
#include <time.h> // убрать

int				main(void)
{
	int			i;
	clock_t		start, end;
	double 		cpu_time_used;
	char 		*map;
	uint64_t	*tetro;
	int			sqrsize;
	node		*tetr;
	char 		letter;
	int			tetramount;

	tetramount = 5;
	tetro = (uint64_t *)malloc(sizeof(uint64_t) * tetramount);
//	tetro[0] = 52224;
//	tetro[1] = 35968;
//	tetro[2] = 27648;
//	tetro[3] = 52224;
//	tetro[4] = 19584;
//	tetro[5] = 57856;
//	tetro[6] = 50240;
//	tetro[7] = 52224;
//	tetro[8] = 27648;
//	tetro[9] = 50240;
//	tetro[10] = 35904;
//	tetro[11] = 58368;
//	tetro[12] = 58368;
	tetro[0] = 52224;
	tetro[1] = 57856;
	tetro[2] = 35008;
	tetro[3] = 50688;
	tetro[4] = 19520;
//	tetro[5] = 35968;
//	tetro[6] = 50688;
//	tetro[7] = 52224;
//	tetro[8] = 57856;
//	tetro[9] = 61440;
//	tetro[10] = 57856;
//	tetro[11] = 50240;
//	tetro[0] = 61440;
//	tetro[0] = 50688;
//	tetro[0] = 34952;
//	tetro[0] = 50240;
//	tetro[0] = 35008;
//	tetro[5] = 50688;
//	tetro[12] = 50688;
//	tetro[13] = 61440;
//	tetro[14] = 35008;
//	tetro[15] = 50688;
	letter = 65;
	start = clock();
	if (!(tetr = createstruct(tetro, tetramount)))
		return (-1);
	if (!(sqrsize = deploy(tetr, tetramount)))
		return (-1);
	if (!(map = map_to_print(sqrsize)))
		return (-1);
	i = 0;
	while (i++ < tetramount)
	{
		map = fillfigure(map, tetr, sqrsize, letter);
		letter++;
		if (tetr->next != NULL)
			tetr = tetr->next;
	}
	freelist(tetr);
	ft_putstr(map);
	free(map);
	free(tetro);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("time %f\n", cpu_time_used);
	return (0);
}
