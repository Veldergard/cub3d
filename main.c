/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/14 20:06:23 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_image_pixel(t_img *image, int x, int y)
{
	return (image->addr + y * image->line_length + x * image->bpp / 8);
}

void	cub_pixel_put(t_g *g, int x, int y, int color)
{
	char	*dst;

	dst = get_image_pixel(&g->img, x, y);
	*(unsigned int*)dst = color;
}

int		cub_draw_line(t_g *g, t_wall *wall)
{
	unsigned int	color;
	float			img_x;
	float			img_y;
	float			step_y;
	int				y;

	img_y = 0;
	if (wall->line_h >= g->win.y)
		img_y = ((float)wall->line_h - g->win.y) / (2 * wall->line_h / CUB_SIZE);
	step_y = ((float)CUB_SIZE) / wall->line_h;
	img_x = (float)((int)(wall->rx) % 64) / CUB_SIZE * wall->text->hgt;
	y = wall->line_o < 0 ? 0 : wall->line_o;
	while (y < wall->line_h + wall->line_o && y >= 0 && y < g->win.y)
	{
		color = *(unsigned int *)get_image_pixel(wall->text, img_x, (int)img_y);
		cub_pixel_put(g, wall->r, y, color);
		img_y += step_y;
		y++;
	}
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
	float	x;
	float	y;

	y = g->player.y - dir * sin(g->player.dir) * SPEED;
	if ((int)(y / 64) >= 0 && (int)(y / 64) < g->map.y &&
			g->map.tab[(int)(y / 64)][(int)(g->player.x / 64)] != '1')
		g->player.y = y;
	x = g->player.x + dir * cos(g->player.dir) * SPEED;
	if ((int)(x / 64) >= 0 && (int)(x / 64) < g->map.x &&
			g->map.tab[(int)(g->player.y / 64)][(int)(x / 64)] != '1')
		g->player.x = x;
}

void	cub_strafe(t_g *g, double dir)
{
	float	x;
	float	y;

	y = g->player.y + dir * cos(g->player.dir) * SPEED;
	if ((int)(y / 64) >= 0 && (int)(y / 64) < g->map.y &&
			g->map.tab[(int)(y / 64)][(int)(g->player.x / 64)] != '1')
		g->player.y = y;
	x = g->player.x + dir * sin(g->player.dir) * SPEED;
	if ((int)(x / 64) >= 0 && (int)(x / 64) < g->map.x &&
			g->map.tab[(int)(g->player.y / 64)][(int)(x / 64)] != '1')
		g->player.x = x;
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
			cub_pixel_put(g, x, y, g->ceiling);
			x++;
		}
		y++;
	}
	while (y < g->win.y)
	{
		x = 0;
		while (x < g->win.x)
		{
			cub_pixel_put(g, x, y, g->floor);
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
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp, &g->img.line_length,
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
	g.ceiling = NONE;
	g.floor = NONE;
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
