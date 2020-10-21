/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_raycaster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 20:30:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 19:45:54 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		cub_set_vertical(t_g *g, t_wall *wall)
{
	if (cos(wall->ray) > 0.001)
	{
		wall->rx = (((int)g->player.x >> 6) << 6) + 64;
		wall->ry = (g->player.x - wall->rx) * wall->m_tan + g->player.y;
		wall->xo = 64;
		wall->yo = -wall->xo * wall->m_tan;
	}
	else if (cos(wall->ray) < -0.001)
	{
		wall->rx = (((int)g->player.x >> 6) << 6) - 2.F / g->win.x;
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
}

static void		cub_check_vertical(t_g *g, t_wall *wall)
{
	wall->dof = 0;
	wall->dis_v = 100000;
	wall->m_tan = tan(wall->ray);
	cub_set_vertical(g, wall);
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
}

static void		cub_set_horizontal(t_g *g, t_wall *wall)
{
	if (sin(wall->ray) > 0.001)
	{
		wall->ry = (((int)g->player.y >> 6) << 6) - 2.F / g->win.x;
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
}

static void		cub_check_horizontal(t_g *g, t_wall *wall)
{
	wall->dof = 0;
	wall->dis_h = 100000;
	wall->m_tan = 1.0 / wall->m_tan;
	cub_set_horizontal(g, wall);
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
}

void			cub_raycaster(t_g *g, t_wall *wall, int *side)
{
	cub_check_vertical(g, wall);
	cub_check_horizontal(g, wall);
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
