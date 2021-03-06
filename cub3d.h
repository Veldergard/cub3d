/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:10:12 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 19:24:06 by olaurine         ###   ########.fr       */
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
# define R_SPD 0.1
# define DOF 64
# define CUB_SIZE 64
# define FOV 1.0471975512F
# define MAP_ERROR -1
# define MALLOC_ERROR -1

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
	int				wdt;
	int				hgt;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_map
{
	char			**tab;
	int				x;
	int				y;
	char			is_parsing;
}					t_map;

typedef struct		s_win
{
	int				x;
	int				y;
	void			*ptr;
}					t_win;

typedef struct		s_wall
{
	int				r;
	int				mx;
	int				my;
	int				dof;
	int				line_h;
	int				line_o;
	float			ca;
	float			vx;
	float			vy;
	float			rx;
	float			ry;
	float			ray;
	float			xo;
	float			yo;
	float			dis_v;
	float			dis_h;
	float			m_tan;
	float			step;
	t_img			*text;
}					t_wall;

typedef struct		s_sprite
{
	int				x;
	int				y;
	float			dist;
}					t_sprite;

typedef struct		s_g
{
	t_win			win;
	t_img			img;
	char			color;
	unsigned int	floor;
	unsigned int	ceiling;
	t_img			n;
	t_img			s;
	t_img			e;
	t_img			w;
	t_map			map;
	t_player		player;
	void			*mlx;
	float			*x_dists;
	t_img			sp;
	t_list			*sprite_lst;
	t_sprite		**sprites;
	int				spr_cnt;
	int				spr_size;
}					t_g;

void				cub_parse(char *file, t_g *g);
int					cub_make_sqr_map(t_g *g);
int					cub_set_player(t_g *g);
int					cub_check_map(t_g *g);
void				cub_draw_walls(t_g *g);
float				cub_dist(float ax, float ay, float bx, float by);
void				cub_draw_sprites(t_g *g);
float				cub_normalize_rad(float rad);
void				cub_draw(t_g *g);
void				cub_bmp(t_g *g);
void				cub_exit(t_g *g, int status, char *msg);
int					cub_skip_spaces(char *line, int *i);
void				cub_parse_texture(t_g *g, t_img *adr, char *line, int *i);
void				cub_parse_map(t_g *g, char *line, int *i);
int					cub_check_cell(t_g *g, int y, int x);
int					cub_check_params(t_g *g);
int					cub_close(t_g *g);
int					cub_key(int key, t_g *g);
void				cub_render_next_frame(t_g *g);
void				cub_draw_line(t_g *g, t_wall *wall, int side);
void				cub_pixel_put(t_g *g, int x, int y, int color);
void				cub_raycaster(t_g *g, t_wall *wall, int *side);
int					cub_check_ending(char *file, char *ext);

#endif
