#ifndef FILE_H
# define FILE_H

typedef struct		s_list
{
	int				id;
	int 			h_axis;
	int 			v_axis;
	struct s_list	*right;
	struct s_list	*left;
	struct s_list	*up;
	struct s_list	*down;
	int 			cell;
}					node;

#endif