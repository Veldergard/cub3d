/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:45:53 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:51:02 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		*cub_get_image_pixel(t_img *image, int x, int y)
{
	return (image->addr + y * image->line_length + x * image->bpp / 8);
}

void			cub_pixel_put(t_g *g, int x, int y, int color)
{
	char	*dst;

	dst = cub_get_image_pixel(&g->img, x, y);
	*(unsigned int*)dst = color;
}

void			cub_draw_line(t_g *g, t_wall *wall, int side)
{
	unsigned int	color;
	float			img_x;
	float			img_y;
	float			step_y;
	int				y;

	img_y = 0;
	if (wall->line_h >= g->win.y)
		img_y = ((float)wall->line_h - g->win.y) /
		(2 * (float)wall->line_h / CUB_SIZE);
	step_y = ((float)CUB_SIZE) / wall->line_h;
	img_x = (float)((int)(wall->rx) % CUB_SIZE) / CUB_SIZE * wall->text->hgt;
	img_x = side == 2 || side == 3 ? CUB_SIZE - img_x : img_x;
	y = wall->line_o < 0 ? 0 : wall->line_o;
	while (y < wall->line_h + wall->line_o && y >= 0 && y < g->win.y)
	{
		color = *(unsigned int *)
			cub_get_image_pixel(wall->text, img_x, (int)img_y);
		cub_pixel_put(g, wall->r, y, color);
		img_y += step_y;
		y++;
	}
}

static void		cub_clear_scene(t_g *g)
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

void			cub_draw(t_g *g)
{
	cub_clear_scene(g);
	cub_draw_walls(g);
	cub_draw_sprites(g);
}
