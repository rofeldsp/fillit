#ifndef FILLIT_H
# define FILLIT_H

# include <stdio.h> // remove later
# include <stdlib.h>
# include "../libft/libft.h" // substitute to libft.h and add trace to makefile

typedef struct		t_list
{
	struct t_list	*next;
	struct t_list	*prev;
	uint64_t		tetromap;
	uint64_t		buff;
	uint64_t		power[64];
	int 			line;
	int 			height;
	int 			width;
}					node;

uint64_t		ftpow(uint64_t number, int power, node *tetr);
int				ft_sqrt_round(int nb);
int				linebreak(node *tetr, int sqrsize);
int				move(node *tetr, int sqrsize);
int				checkmap(uint16_t *map, int sqrsize, node *tetr);
int				moveprevnode(uint16_t *map, int sqrsize, node *tetr);
int				fill_map(uint16_t *map, int sqrsize, node *tetr);
uint16_t		*create_map(void);
node			*move_tetrs_back(node *tetr);
int				deploy(node *tetr, int tetramount);
int				checkheight(node *tetr);
int				checkwidth(node *tetr);
char			*map_to_print(int sqrsize);
char			*fillfigure(char *map, node *tetr, int sqrsize, char letter);
node			*addnode(uint64_t *t, node *head, int tetrnum);
void			freelist(node *tetr);
node			*createstruct(uint64_t *t, int tetramount);

#endif
