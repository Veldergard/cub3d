# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 22:59:15 by olaurine          #+#    #+#              #
#    Updated: 2020/08/27 17:37:57 by olaurine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = main.c cub_parser.c
OBJ = $(patsubst %.c,%.o,$(SRC))
LIBFT = libft
CC = gcc
CFLAGS = -g -Wall -Wextra -Imlx_lnx
OFLAGS = -Imlx_lnx -Lmlx_lnx -lmlx -L$(LIBFT) -lft -lXext -lX11 -lm -lbsd

.PHONY: all clean fclean re

all: libft/libft.a $(NAME)

libft/libft.a:
	make all -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(OFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	/bin/rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	/bin/rm -rf $(NAME)

re: fclean all
