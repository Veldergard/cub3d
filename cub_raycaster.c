/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 20:30:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:57:49 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_raycaster(t_g *g, t_wall *wall, int *side)
{
	wall->dof = 0;
	wall->dis_v = 100000;
	wall->m_tan = tan(wall->ray);
	if (cos(wall->ray) > 0.001)
	{
		wall->rx = (((int)g->player.x >> 6) << 6) + 64;
		wall->ry = (g->player.x - wall->rx) * wall->m_tan + g->player.y;
		wall->xo = 64;
		wall->yo = -wall->xo * wall->m_tan;
	}
	else if (cos(wall->ray) < -0.001)
	{
		wall->rx = (((int)g->player.x >> 6) << 6) - 0.0001;
		wall->ry = (g->player.x - wall->rx) * wall->m_tan + g->player.y;
		wall->xo = -64;
		wall->yo = -wall->xo * wall->m_tan;
	}
	else
	{
		wall->rx = g->player.x;
		wall->ry = g->player.y;
		wall->dof = DOF;
	}
	while (wall->dof < DOF)
	{
		wall->mx = (int)(wall->rx) >> 6;
		wall->my = (int)(wall->ry) >> 6;
		if (wall->mx >= 0 && wall->my >= 0 && wall->mx < g->map.x &&
		wall->my < g->map.y && g->map.tab[wall->my][wall->mx] == '1')
		{
			wall->dof = DOF;
			wall->dis_v = cos(wall->ray) * (wall->rx - g->player.x) -
				sin(wall->ray) * (wall->ry - g->player.y);
		}
		else
		{
			wall->rx += wall->xo;
			wall->ry += wall->yo;
			wall->dof += 1;
		}
	}
	wall->vx = wall->rx;
	wall->vy = wall->ry;
	wall->dof = 0;
	wall->dis_h = 100000;
	wall->m_tan = 1.0 / wall->m_tan;
	if (sin(wall->ray) > 0.001)
	{
		wall->ry = (((int)g->player.y >> 6) << 6) - 0.0001;
		wall->rx = (g->player.y - wall->ry) * wall->m_tan + g->player.x;
		wall->yo = -64;
		wall->xo = -wall->yo * wall->m_tan;
	}
	else if (sin(wall->ray) < -0.001)
	{
		wall->ry = (((int)g->player.y >> 6) << 6) + 64;
		wall->rx = (g->player.y - wall->ry) * wall->m_tan + g->player.x;
		wall->yo = 64;
		wall->xo = -wall->yo * wall->m_tan;
	}
	else
	{
		wall->rx = g->player.x;
		wall->ry = g->player.y;
		wall->dof = DOF;
	}
	while (wall->dof < DOF)
	{
		wall->mx = (int)(wall->rx) >> 6;
		wall->my = (int)(wall->ry) >> 6;
		if (wall->mx >= 0 && wall->my >= 0 && wall->mx < g->map.x &&
		wall->my < g->map.y && g->map.tab[wall->my][wall->mx] == '1')
		{
			wall->dof = DOF;
			wall->dis_h = cos(wall->ray) * (wall->rx - g->player.x) -
				sin(wall->ray) * (wall->ry - g->player.y);
		}
		else
		{
			wall->rx += wall->xo;
			wall->ry += wall->yo;
			wall->dof += 1;
		}
	}
	if (wall->dis_v < wall->dis_h)
	{
		wall->dis_h = wall->dis_v;
		wall->text = wall->ray >= PI2 && wall->ray <= PI3 ? &(g->w) : &(g->e);
		*side = wall->ray >= PI2 && wall->ray <= PI3 ? 2 : 0;
		wall->rx = wall->vy;
		wall->ry = wall->vy;
	}
	else
	{
		wall->text = wall->ray >= 0 && wall->ray <= PI ? &(g->n) : &(g->s);
		*side = wall->ray >= 0 && wall->ray <= PI ? 1 : 3;
	}
}

void	cub_draw_walls(t_g *g)
{
	t_wall	wall;
	int		side;

	wall.r = 0;
	wall.ray = cub_normalize_rad(g->player.dir + FOV / 2);
	wall.step = FOV / (float)g->win.x;
	while (wall.r < g->win.x)
	{
		cub_raycaster(g, &wall, &side);
		wall.ca = g->player.dir - wall.ray;
		wall.dis_h = wall.dis_h * cos(wall.ca);
		g->x_dists[wall.r] = wall.dis_h;
		wall.line_h = (CUB_SIZE * g->win.y) / wall.dis_h;
		wall.line_o = 0;
		if (wall.line_h < g->win.y)
			wall.line_o = (int)(g->win.y - wall.line_h) / 2;
		cub_draw_line(g, &wall, side);
		wall.ray = cub_normalize_rad(wall.ray - wall.step);
		wall.r++;
	}
}
