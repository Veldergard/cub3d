/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/06 21:47:24 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_pixel_put(t_g *g, int x, int y, int color)
{
	char	*dst;

	dst = g->img.addr + y * g->img.line_length + x * (g->img.bits_per_pixel / 8);
	*(unsigned int*)dst = color;
}

float	cub_dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int		cub_draw_line(t_g *g, int x, float lineO, float lineH)
{
	int y;

	y = lineO;
	while (y < lineH && y > 0 && y < g->win.y)
		cub_pixel_put(g, x, y++, 0x28d4b1);
	return (1);
}

void	cub_draw_walls(t_g *g)
{
	int		r;
	int		depth_of_field;
	int		x_offset;
	int		y_offset;
	int		map_x;
	int		map_y;
	float	ray;
	float	arc_tan;
	float	not_tan;
	float	ray_x;
	float	ray_y;
	float	disH;
	float	disV;
	float	hx;
	float	vx;
	float	hy;
	float	vy;
	float	dist;
	float	lineH;
	float	ca;
	float	lineO;
	float	step;

	r = 0;
	ray = g->player.dir - DR * 30;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray > 2 * PI ? ray - 2 * PI : ray;
	step = 60. * DR / (float)g->win.x;
	while (r < g->win.x)
	{
		// Vertical
		depth_of_field = 0;
		disV = 1000000;
		vx = g->player.x;
		vy = g->player.y;
		not_tan = -tan(ray);
		if (ray > PI2 && ray < PI3)
		{
			ray_x = (((int)g->player.x >> 6) << 6) - 0.0001;
			ray_y = (g->player.x - ray_x) * not_tan + g->player.y;
			x_offset = -64;
			y_offset = -x_offset * not_tan;
		}
		else if (ray < PI2 || ray > PI3)
		{
			ray_x = (((int)g->player.x >> 6) << 6) + 64;
			ray_y = (g->player.x - ray_x) * not_tan + g->player.y;
			x_offset = 64;
			y_offset = -x_offset * not_tan;
		}
		else
		{
			ray_x = g->player.x;
			ray_y = g->player.y;
			depth_of_field = DOF;
		}
		while (depth_of_field < DOF)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_y) >> 6;
			if (map_x > 0 && map_y > 0 &&
				map_y < g->map.y && map_x < g->map.x &&
				g->map.tab[map_y][map_x] == '1')
			{
				vx = ray_x;
				vy = ray_y;
				disV = cub_dist(g->player.x, g->player.y, vx, vy);
				depth_of_field = DOF;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		// Horizontal
		depth_of_field = 0;
		disH = 1000000;
		hx = g->player.x;
		hy = g->player.y;
		arc_tan = -1 / tan(ray);
		if (ray > PI)
		{
			ray_y = (((int)g->player.y >> 6) << 6) - 0.0001;
			ray_x = (g->player.y - ray_y) * arc_tan + g->player.x;
			y_offset = -64;
			x_offset = -y_offset * arc_tan;
		}
		else if (ray < PI)
		{
			ray_y = (((int)g->player.y >> 6) << 6) + 64;
			ray_x = (g->player.y - ray_y) * arc_tan + g->player.x;
			y_offset = 64;
			x_offset = -y_offset * arc_tan;
		}
		else
		{
			ray_x = g->player.x;
			ray_y = g->player.y;
			depth_of_field = DOF;
		}
		while (depth_of_field < DOF)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_y) >> 6;
			if (map_x > 0 && map_y > 0 &&
				map_y < g->map.y && map_x < g->map.x &&
				g->map.tab[map_y][map_x] == '1')
			{
				hx = ray_x;
				hy = ray_y;
				disH = cub_dist(g->player.x, g->player.y, hx, hy);
				depth_of_field = DOF;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		if (disV < disH)
		{
			ray_x = vx;
			ray_y = vy;
			dist = disV;
		}
		else if (disH < disV)
		{
			ray_x = hx;
			ray_y = hy;
			dist = disH;
		}
		ca = g->player.dir - ray;
		ca = ca < 0 ? ca + 2 * PI : ca;
		ca = ca > 2 * PI ? ca - 2 * PI : ca;
		dist = dist * cos(ca); // fix fisheye
		lineH = (CUB_SIZE * g->win.y) / dist;
		lineH = lineH > g->win.y ? g->win.y : lineH;
		lineO = (int)(g->win.y - lineH) / 2; // line offset
		cub_draw_line(g, r, lineO, lineH + lineO);
		ray += step;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray > 2 * PI ? ray - 2 * PI : ray;
		r++;
	}
}

void	cub_rotate(t_g *g, double dir)
{
	g->player.dir += dir * R_SPD;
	while (g->player.dir < 0)
		g->player.dir += 2 * PI;
	while (g->player.dir > 2 * PI)
		g->player.dir -= 2 * PI;
}

void	cub_move(t_g *g, double dir)
{
	g->player.y += dir * sin(g->player.dir) * SPEED;
	g->player.x += dir * cos(g->player.dir) * SPEED;
}

void	cub_strafe(t_g *g, double dir)
{
	g->player.y -= dir * cos(g->player.dir) * SPEED;
	g->player.x += dir * sin(g->player.dir) * SPEED;
}

int		cub_close(t_g *g)
{
	exit(0);
	return (g->error);
}

void	cub_clear_scene(t_g *g)
{
	int y;
	int x;

	y = 0;
	while (y < (int)(g->win.y / 2))
	{
		x = 0;
		while (x < g->win.x)
		{
			cub_pixel_put(g, x, y, 0x4287f5);
			x++;
		}
		y++;
	}
	while (y < g->win.y)
	{
		x = 0;
		while (x < g->win.x)
		{
			cub_pixel_put(g, x, y, 0xd742f5);
			x++;
		}
		y++;
	}
}

int		cub_render_next_frame(t_g *g)
{
	cub_clear_scene(g);
	cub_draw_walls(g);
	mlx_put_image_to_window(g->mlx, g->win.ptr, g->img.img, 0, 0);
	mlx_do_sync(g->mlx);
	return (g->error);
}

int		cub_key(int key, t_g *g)
{
	if (key == ESC)
		cub_close(g);
	else if (key == W)
		cub_move(g, 1);
	else if (key == A)
		cub_strafe(g, 1);
	else if (key == S)
		cub_move(g, -1);
	else if (key == D)
		cub_strafe(g, -1);
	else if (key == LEFT)
		cub_rotate(g, -1);
	else if (key == RIGHT)
		cub_rotate(g, 1);
	cub_render_next_frame(g);
	return (1);
}

int		cub_start(t_g *g)
{
	g->win.ptr = mlx_new_window(g->mlx, g->win.x, g->win.y, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->win.x, g->win.y);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel, &g->img.line_length,
								&g->img.endian);
	cub_render_next_frame(g);
	mlx_do_key_autorepeaton(g->mlx);
	mlx_hook(g->win.ptr, 2, 1L<<0, cub_key, g);
	mlx_hook(g->win.ptr, 17, 1L<<17, cub_close, g);
	mlx_loop(g->mlx);
	return (1);
}

int		cub_bitmap(t_g *g)
{
	return (g->error);
}

int		cub_init(char *cub, int bmp)
{
	t_g		g;

	ft_bzero(&g, sizeof(g));
	g.text.ceiling = NONE;
	g.text.floor = NONE;
	g.mlx = mlx_init();
	cub_parse(cub, &g);
	cub_make_sqr_map(&g);
	cub_set_player(&g);
	cub_check_map(&g);
	if (bmp == 1)
		return (cub_bitmap(&g));
	cub_start(&g);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		cub_init(av[1], 1);
	else if (ac == 2)
		cub_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
