//#include "fillit.h"
#include "../includes/fillit.h"

uint64_t		ftpow(uint64_t number, int power, node *tetr)
{
	if (power == 2)
		return (number * number);
	else if (power == 1)
		return (number);
	else if (power == 0)
		return (1);
	return (number = number * tetr->power[power - 1]);
}


