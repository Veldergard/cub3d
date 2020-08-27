/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:10:12 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 01:42:13 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define NONE 0xFF000000

typedef struct		s_map
{
	char			**tab;
	int				x;
	int				y;
	int				spr;
}					t_map;

typedef struct	s_texture
{
	unsigned int	*n; // north
	unsigned int	*s; // south
	unsigned int	*e; // east
	unsigned int	*w; // west
	unsigned int	*sp; //sprite
	unsigned int	floor; //floor color
	unsigned int	ceiling; // ceiling color
}				t_texture;

typedef struct	s_window
{
	int				x; // width of window
	int				y; // height of window
}				t_window;

typedef struct	s_data
{
	t_window	window;
	t_texture	texture;
	int			error; // error code
	t_map		map;
}				t_data;

int				cub_parse(char *file, t_data *data);

#endif
