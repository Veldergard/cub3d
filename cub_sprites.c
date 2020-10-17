/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:14:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/17 15:49:46 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_sprite_image_pixel(t_g *g, t_img *img, int x, int y)
{
	x = (int)((float)x / g->spr_size * CUB_SIZE);
	y = (int)((float)y / g->spr_size * CUB_SIZE);
	return (*(uint32_t*)(img->addr + y * img->line_length + x * img->bpp / 8));
}

void			draw_the_sprite(t_g *g, int y_off, int x_off, float dist)
{
	int			i;
	int			j;
	uint32_t	color;
	float 		dst;

	i = (y_off < 0 ? -y_off : 0) - 1;
	while (++i < g->spr_size)
	{
		if (y_off + i >= g->win.y)
			continue;
		j = (x_off < 0 ? -x_off : 0) - 1;
		while (++j < g->spr_size)
		{
			dst = g->x_dists[x_off + j];
			if (x_off + j >= g->win.x || dist > g->x_dists[x_off + j])
				continue;
			color = get_sprite_image_pixel(g, &g->sp, j, i);
			if (color & 0xFFFFFF)
				cub_pixel_put(g, x_off + j, y_off + i, color);
		}
	}
}

void			draw_sprite(t_g *g, t_sprite *sprite)
{
	float	sprite_dir;
	float	sprite_dist;
	int		size;
	int		x_off;
	int		y_off;

	sprite_dir = atan2f(sprite->y - g->player.y, sprite->x - g->player.x);
	sprite_dir = cub_normalize_rad(sprite_dir + g->player.dir);
	if (sprite_dir > PI)
		sprite_dir -= 2.F * PI;
	sprite_dist = cub_dist(g->player.x, g->player.y, sprite->x, sprite->y);
	size = g->win.x / sprite_dist * CUB_SIZE;
	if (size > 4 * g->win.x || size > 4 * g->win.y)
		return ;
	x_off = sprite_dir * g->win.x / FOV + (g->win.x - size) / 2;
	y_off = (g->win.y - size) / 2;
	g->spr_size = size;
	if (x_off + size > 0 && x_off - size < g->win.x)
		draw_the_sprite(g, y_off, x_off, sprite_dist);
}

void			cub_sort_sprites(t_g *g)
{
	t_sprite	*swap;
	int			i;
	int			j;

	i = -1;
	while (++i < g->spr_cnt)
		g->sprites[i]->dist = cub_dist(g->player.x, g->player.y,
			g->sprites[i]->x, g->sprites[i]->y);
	i = 0;
	while (i < g->spr_cnt - 1)
	{
		j = i + 1;
		while (j < g->spr_cnt)
		{
			if (g->sprites[i]->dist < g->sprites[j]->dist)
			{
				swap = g->sprites[i];
				g->sprites[i] = g->sprites[j];
				g->sprites[j] = swap;
			}
			j++;
		}
		i++;
	}
}

void			cub_draw_sprites(t_g *g)
{
	int		i;

	cub_sort_sprites(g);
	i = 0;
	while (i < g->spr_cnt)
	{
		draw_sprite(g, g->sprites[i]);
		i++;
	}
}
