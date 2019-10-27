# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofeldsp <rofeldsp@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/27 13:14:43 by rofeldsp          #+#    #+#              #
#    Updated: 2019/10/27 16:45:42 by rofeldsp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

INP = srcs/main.c \
		srcs/solver_1.c \
		srcs/solver_2.c \
		srcs/freelinkedlist.c \
		srcs/create_tetris.c \
		srcs/ft_sqrt_round.c \
		srcs/print_tetris.c \
		srcs/ft_power_fillit.c

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): lib
	@gcc $(FLAGS) $(INP) -I includes -I libft -L libft/ -lft -o $(NAME)

lib:
	@make -C libft

clean:
	@make -C libft clean

fclean:
	@make -C libft fclean
	@/bin/rm -f $(NAME)

re: fclean all