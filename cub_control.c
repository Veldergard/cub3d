/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:42:45 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:50:46 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		cub_rotate(t_g *g, double dir)
{
	g->player.dir -= dir * R_SPD;
	while (g->player.dir < 0)
		g->player.dir += 2 * PI;
	while (g->player.dir > 2 * PI)
		g->player.dir -= 2 * PI;
}

static void		cub_move(t_g *g, double dir)
{
	float	x;
	float	y;

	y = g->player.y - dir * sin(g->player.dir) * SPEED;
	if ((int)(y / CUB_SIZE) >= 0 && (int)(y / CUB_SIZE) < g->map.y &&
		g->map.tab[(int)(y / CUB_SIZE)][(int)(g->player.x / CUB_SIZE)] != '1')
		g->player.y = y;
	x = g->player.x + dir * cos(g->player.dir) * SPEED;
	if ((int)(x / CUB_SIZE) >= 0 && (int)(x / CUB_SIZE) < g->map.x &&
		g->map.tab[(int)(g->player.y / CUB_SIZE)][(int)(x / CUB_SIZE)] != '1')
		g->player.x = x;
}

static void		cub_strafe(t_g *g, double dir)
{
	float	x;
	float	y;

	y = g->player.y - dir * cos(g->player.dir) * SPEED;
	if ((int)(y / CUB_SIZE) >= 0 && (int)(y / CUB_SIZE) < g->map.y &&
		g->map.tab[(int)(y / CUB_SIZE)][(int)(g->player.x / CUB_SIZE)] != '1')
		g->player.y = y;
	x = g->player.x - dir * sin(g->player.dir) * SPEED;
	if ((int)(x / CUB_SIZE) >= 0 && (int)(x / CUB_SIZE) < g->map.x &&
		g->map.tab[(int)(g->player.y / CUB_SIZE)][(int)(x / CUB_SIZE)] != '1')
		g->player.x = x;
}

int				cub_close(t_g *g)
{
	cub_exit(g, 1, NULL);
	return (1);
}

int				cub_key(int key, t_g *g)
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
