#ifndef FILE_H
# define FILE_H

# include <stdio.h> // remove later
# include <stdlib.h>
# include "libft/libft.h" // substitute to libft.h and add trace to makefile

typedef struct		t_list
{
	struct t_list	*next;
	struct t_list	*prev;
	uint64_t		tetromap;
	uint64_t		buff;
	unsigned short	power[64];
	int 			line;
	//int 			tetromino; // шифрованная в 16 битах последовательность
	// расположения фигур, и надо держать еще формулу расположения по
	// координатам
	int 			width;
}					node;

#endif
