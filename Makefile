# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 22:59:15 by olaurine          #+#    #+#              #
#    Updated: 2020/10/16 17:09:23 by olaurine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = main.c cub_parser.c map_checker.c raycaster.c utils.c cub_sprites.c
OBJ = $(patsubst %.c,%.o,$(SRC))
LIBFT = libft
CC = gcc
CFLAGS = -g -Wall -Wextra -Imlx_lnx
# OFLAGS = -Imlx_lnx -Lmlx_lnx -lmlx -L$(LIBFT) -lft -lXext -lX11 -lm -lbsd
OFLAGS = -L$(LIBFT) -lft -lm -framework OpenGL -framework AppKit -lmlx

.PHONY: all clean fclean re

all: libft/libft.a $(NAME)

libft/libft.a:
	make all -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(OFLAGS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	/bin/rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	/bin/rm -rf $(NAME)

re: fclean all
