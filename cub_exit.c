/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:01:28 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/19 19:52:39 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_free_map(t_g *g)
{
	int		i;

	i = 0;
	while (i < g->map.y)
	{
		free(g->map.tab[i]);
		i++;
	}
	free(g->map.tab);
}

void	cub_free(t_g *g)
{
	if (g->s.img)
		mlx_destroy_image(g->mlx, g->s.img);
	if (g->n.img)
		mlx_destroy_image(g->mlx, g->n.img);
	if (g->e.img)
		mlx_destroy_image(g->mlx, g->e.img);
	if (g->w.img)
		mlx_destroy_image(g->mlx, g->w.img);
	if (g->sp.img)
		mlx_destroy_image(g->mlx, g->sp.img);
	if (g->sprites)
		free(game->sprites);
	if (g->x_dists)
		free(g->x_dists);
	if (g->mlx)
		free (g->mlx);
}

void	cub_exit(t_g *g, int status, char *msg)
{
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->win.ptr && status != -1)
		mlx_destroy_window(g->mlx, g->win.ptr);
	if (g->map.tab)
		cub_free_map(g);
	cub_free(g);
	ft_bzero(game, sizeof(*game));
	if (status > 0)
	{
		ft_putendl_fd("Error!", 2);
		if (msg)
			ft_putendl_fd(msg, 2);
	}
	exit(status < 0 ? 0 : status);
}
