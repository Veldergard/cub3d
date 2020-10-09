/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/08 20:55:15 by olaurine         ###   ########.fr       */
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
