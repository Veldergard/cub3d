/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:46:25 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_render_next_frame(t_g *g)
{
	cub_draw(g);
	mlx_put_image_to_window(g->mlx, g->win.ptr, g->img.img, 0, 0);
	mlx_do_sync(g->mlx);
}

void	cub_start(t_g *g)
{
	g->win.ptr = mlx_new_window(g->mlx, g->win.x, g->win.y, "cub3D");
	g->img.img = mlx_new_image(g->mlx, g->win.x, g->win.y);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
									&g->img.line_length, &g->img.endian);
	cub_render_next_frame(g);
	mlx_do_key_autorepeaton(g->mlx);
	mlx_hook(g->win.ptr, 2, 1L << 0, cub_key, g);
	mlx_hook(g->win.ptr, 17, 1L << 17, cub_close, g);
	mlx_loop(g->mlx);
}

void	cub_init(char *cub, int bmp)
{
	t_g		g;

	ft_bzero(&g, sizeof(g));
	g.ceiling = NONE;
	g.floor = NONE;
	g.mlx = mlx_init();
	cub_parse(cub, &g);
	if (!(cub_make_sqr_map(&g)))
		cub_exit(&g, -1, "Malloc error!");
	if (!(cub_set_player(&g)))
		cub_exit(&g, -1, "Player setting error!");
	if (!(cub_check_map(&g)))
		cub_exit(&g, -1, "Map error!");
	if (bmp)
		cub_bmp(&g);
	else
		cub_start(&g);
}

int		main(int ac, char **av)
{
	if (ac == 3 && !ft_strcmp(av[2], "--save"))
		cub_init(av[1], 1);
	else if (ac == 2)
		cub_init(av[1], 0);
	else
		write(2, "Error\n Invalid arguments!\n", 26);
	return (0);
}
