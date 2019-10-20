#ifndef FILE_H
# define FILE_H

typedef struct		s_list
{
	struct s_list	*next;
	unsigned int	tetromap[16];
	//int 			tetromino; // шифрованная в 16 битах последовательность
	// расположения фигур, плюс надо держать еще формулу расположения по координатам
	int 			width;
}					node;

#endif