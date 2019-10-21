#ifndef FILE_H
# define FILE_H

# include <stdio.h> // remove later
# include <stdlib.h>
# include <libft/libft.h> // substitute to libft.h and add trace to makefile

typedef struct		s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	unsigned short	tetromap[16];
	//int 			tetromino; // шифрованная в 16 битах последовательность
	// расположения фигур, плюс надо держать еще формулу расположения по координатам
	int 			width;
}					node;

#endif