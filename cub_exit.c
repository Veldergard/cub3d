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
	if (g->map.tab)
		cub_free_map(g);
	if (g->so_tex.image)
		mlx_destroy_image(game->mlx, game->so_tex.image);
	if (g->no_tex.image)
		mlx_destroy_image(game->mlx, game->no_tex.image);
	if (g->ea_tex.image)
		mlx_destroy_image(game->mlx, game->ea_tex.image);
	if (g->we_tex.image)
		mlx_destroy_image(game->mlx, game->we_tex.image);
	if (g->sprite.image)
		mlx_destroy_image(game->mlx, game->sprite.image);
	if (g->sprites)
		free(game->sprites);
	if (g->x_dists)
		free(g->x_dists);
	if (g->mlx)
		free (g->mlx);
}

void	cub_exit(t_g *g, int status, char *msg)
{
	exit(status < 0 ? 0 : status);
}
