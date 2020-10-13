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

void cub_draw_walls(t_g *g)
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	int		line_h;
	int		line_o;
	float	ca;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ray;
	float	xo;
	float	yo;
	float	dis_v;
	float	dis_h;
	float	m_tan;
	float	step;
	t_img	*text;

	r = 0;
	ray = g->player.dir - 30 * DR;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray >= 2 * PI ? ray - 2 * PI : ray;
	step = 60. * DR / (float)g->win.x;
	while (r < g->win.x)
	{
		dof = 0;
		dis_v = 100000;
		m_tan = tan(ray);
		if (cos(ray) > 0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) + 64;
			ry = (g->player.x - rx) * m_tan + g->player.y;
			xo = 64;
			yo = -xo * m_tan;
		}
		else if (cos(ray) < -0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) - 0.0001;
			ry = (g->player.x - rx) * m_tan + g->player.y;
			xo = -64;
			yo = -xo * m_tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if(mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = DOF;
				dis_v = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
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
		dis_h = 100000;
		m_tan = 1.0 / m_tan;
		if (sin(ray) > 0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) - 0.0001;
			rx = (g->player.y - ry) * m_tan + g->player.x;
			yo = -64;
			xo = -yo * m_tan;
		}
		else if (sin(ray) < -0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) + 64;
			rx = (g->player.y - ry) * m_tan + g->player.x;
			yo = 64;
			xo = -yo * m_tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = DOF;
		}
		while (dof < DOF)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = DOF;
				dis_h = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (dis_v < dis_h)
		{
			dis_h = dis_v;
			text = ray >= PI2 && ray <= PI3 ? &(g->w) : &(g->e);
            rx = vy;
            ry = vy;
		}
		else
        {
            text = ray >= 0 && ray <= PI ? &(g->n) : &(g->s);
        }
		ca = g->player.dir - ray;
		dis_h = dis_h * cos(ca);
		line_h = (CUB_SIZE * g->win.y) / dis_h;
		line_h = line_h > g->win.y ? g->win.y : line_h;
		line_o = (int)(g->win.y - line_h) / 2;
		cub_draw_line(g, r, line_o, line_h + line_o, (int)rx % 64, (int)ry % 64, text);
		ray += step;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray >= 2 * PI ? ray - 2 * PI : ray;
		r++;
    }
}
