/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 20:30:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/08 20:58:09 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cub_drayw_walls(t_g *g)
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	int		lineH;
	int		lineO;
	float	ca;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ray;
	float	xo;
	float	yo;
	float	disV;
	float	disH;
	float	Tan;
	float	step;

	r = 0;
	ray = g->player.dir - 30 * DR;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray > 2 * PI ? ray - 2 * PI : ray;
	step = 60. * DR / (float)g->win.x;
	while (r < g->win.x)
	{
		dof = 0;
		disV = 100000;
		Tan = tan(ray);
		if (cos(ray) > 0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) + 64;
			ry = (g->player.x - rx) * Tan + g->player.y;
			xo = 64;
			yo = -xo * Tan;
		}
		else if (cos(ray) < -0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) - 0.0001;
			ry = (g->player.x - rx) * Tan + g->player.y;
			xo = -64;
			yo = -xo * Tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if(mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = 8;
				disV = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;

		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(ray) > 0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) - 0.0001;
			rx = (g->player.y - ry) * Tan + g->player.x;
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(ray) < -0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) + 64;
			rx = (g->player.y - ry) * Tan + g->player.x;
			yo = 64;
			xo = -yo * Tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = 8;
				disH = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
			disH = disV;
		ca = g->player.dir - ray;
		disH = disH * cos(ca);
		lineH = (CUB_SIZE * g->win.y) / disH;
		lineH = lineH > g->win.y ? g->win.y : lineH;
		lineO = (int)(g->win.y - lineH) / 2;
		cub_draw_line(g, r, lineO, lineH + lineO);
		// ray -= ray - 1 * DR;
		ray += step;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray > 2 * PI ? ray - 2 * PI : ray;
		r++;
	}
}
