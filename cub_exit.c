/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:01:28 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/20 19:04:11 by olaurine         ###   ########.fr       */
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
	if (g->map.y > 0)
		free(g->map.tab);
}

void	cub_free_sprites(t_g *g)
{
	int i;

	i = 0;
	while (g->sprites[i])
	{
		free(g->sprites[i]);
		i++;
	}
	free(g->sprites);
	while (g->sprite_lst)
		free(ft_lstpop_left(&g->sprite_lst));
}

void	cub_free(t_g *g)
{
	if (g->map.tab)
		cub_free_map(g);
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
		cub_free_sprites(g);
	if (g->x_dists)
		free(g->x_dists);
	if (g->mlx)
		free(g->mlx);
}

void	cub_exit(t_g *g, int status, char *msg)
{
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->win.ptr && status != -1)
		mlx_destroy_window(g->mlx, g->win.ptr);
	cub_free(g);
	ft_bzero(g, sizeof(*g));
	if (status == -1)
	{
		ft_putendl_fd("Error", 2);
		if (msg)
			ft_putendl_fd(msg, 2);
	}
	exit(status < 0 ? 0 : status);
}
