/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:10:12 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 17:34:28 by olaurine         ###   ########.fr       */
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
# include <math.h>
# include "mlx.h"

# define NONE 0xFF000000
# define PI 3.14159265359
# define PI2 PI / 2
# define PI3 3 * PI / 2

typedef struct		s_player
{
	float			x;
	float			y;
	float			dir;
	char			chr;
}					t_player;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_map
{
	char			**tab;
	int				x;
	int				y;
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
	t_player	player;
}				t_data;

int				cub_parse(char *file, t_data *data);

#endif
