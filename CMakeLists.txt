cmake_minimum_required(VERSION 3.14)
project(fillit_own_git C)

set(CMAKE_C_STANDARD 11)

add_executable(fillit_own_git
        includes/fillit.h
        libft/ft_putstr.c
        libft/ft_putchar.c
        srcs/create_tetris.c
        srcs/freelinkedlist.c
        srcs/ft_power_fillit.c
        srcs/ft_sqrt_round.c
        srcs/main.c
        srcs/print_tetris.c
        srcs/solver_1.c
        srcs/solver_2.c)
