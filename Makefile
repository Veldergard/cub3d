# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 22:59:15 by olaurine          #+#    #+#              #
#    Updated: 2020/08/21 23:01:46 by olaurine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC =
OBJ = $(patsubst %.c,%.o,$(SRC))
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: libft/libft.a $(NAME)

libft/libft.a:
	make all -C libft

$(NAME): $(OBJ)
	@[ -f $@ ] || cp libft/libft.a $(NAME)
	ar rcs $(NAME) $?

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	/bin/rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	/bin/rm -rf $(NAME)

re: fclean all
