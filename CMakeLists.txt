cmake_minimum_required(VERSION 3.14)
project(fillit C)

set(CMAKE_C_STANDARD 11)

add_executable(fillit.h
        main.c
        libft/libft.h)
