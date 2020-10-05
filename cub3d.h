/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:10:12 by olaurine          #+#    #+#             */
/*   Updated: 2020/09/10 20:15:15 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include "libft/libft.h"
# include <math.h>
# include "mlx.h"

# define NONE 0xFF000000
# define PI 3.14159265359
# define PI2 PI / 2
# define PI3 3 * PI / 2
# define DR 0.0174533

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

typedef struct		s_rect
{
	int				x;
	int				y;
}					t_rect;

typedef struct		s_mlx
{
	void			*ptr;
}					t_mlx;

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

typedef struct		s_text
{
	unsigned int	*n; // north
	unsigned int	*s; // south
	unsigned int	*e; // east
	unsigned int	*w; // west
	unsigned int	*sp; //sprite
	unsigned int	floor; //floor color
	unsigned int	ceiling; // ceiling color
}					t_text;

typedef struct		s_win
{
	int				x; // width of window
	int				y; // height of window
	void			*ptr;
}					t_win;

typedef struct		s_g
{
	t_win			win;
	t_text			text;
	int				error; // error code
	t_map			map;
	t_player		player;
	t_mlx			mlx;
	t_img			img;
	t_rect			rect;
}					t_g;

int					cub_parse(char *file, t_g *g);
char				*cub_make_str(t_g *g, int i);
int					cub_make_sqr_map(t_g *g);
void				cub_set_dir(t_g *g, char c);
int					cub_set_player(t_g *g);
int					cub_check_map(t_g *g);

#endif
