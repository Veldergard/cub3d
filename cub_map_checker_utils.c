/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_checker_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:07:30 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 18:23:16 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub_is_inner_chr(char c)
{
	if (c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int			cub_check_cell(t_g *g, int y, int x)
{
	if ((x == 0 || y == 0 || x == g->map.x - 1 || y == g->map.y - 1)
	&& !cub_is_inner_chr(g->map.tab[y][x]))
		return (1);
	if ((x > 0 && y > 0 && x < g->map.x - 1 && y < g->map.y - 1)
	&& cub_is_inner_chr(g->map.tab[y][x])
	&& (cub_is_inner_chr(g->map.tab[y - 1][x]) || g->map.tab[y - 1][x] == '1')
	&& (cub_is_inner_chr(g->map.tab[y + 1][x]) || g->map.tab[y + 1][x] == '1')
	&& (cub_is_inner_chr(g->map.tab[y][x - 1]) || g->map.tab[y][x - 1] == '1')
	&& (cub_is_inner_chr(g->map.tab[y][x + 1]) || g->map.tab[y][x + 1] == '1'))
		return (1);
	else if ((x > 0 && y > 0 && x < g->map.x - 1 && y < g->map.y - 1)
	&& (!cub_is_inner_chr(g->map.tab[y][x]) ||  g->map.tab[y][x] == '1'))
		return (1);
	return (0);
}
