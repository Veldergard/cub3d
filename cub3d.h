/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:10:12 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/08 20:49:28 by olaurine         ###   ########.fr       */
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
# define SPEED 10
# define R_SPD 0.05
# define DOF 64
# define CUB_SIZE 64

# ifdef __APPLE__

#  define A		0x0
#  define D		0x2
#  define S		0x1
#  define W		0xD
#  define ESC	0x35
#  define LEFT	0x7B
#  define RIGHT	0x7C

# else

#  define A		0x61
#  define D		0x64
#  define S		0x73
#  define W		0x77
#  define ESC		0xff1b
#  define LEFT	0xff51
#  define RIGHT	0xff53

# endif

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
	void			*mlx;
	t_img			img;
}					t_g;

int					cub_parse(char *file, t_g *g);
char				*cub_make_str(t_g *g, int i);
int					cub_make_sqr_map(t_g *g);
void				cub_set_dir(t_g *g, char c);
int					cub_set_player(t_g *g);
int					cub_check_map(t_g *g);
void				cub_draw_walls(t_g *g);
int					cub_draw_line(t_g *g, int x, float lineO, float lineH);


#endif
