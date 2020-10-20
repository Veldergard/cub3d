/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:38:26 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/20 16:54:59 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(t_img *i, int x, int y)
{
	char	*dst;

	dst = i->addr + (y * i->line_length + x * (i->bpp / 8));
	return (*(unsigned int*)dst);
}

void			cub_bitmap(t_g *g, int fd)
{
	int		i;
	int		j;
	int		color;

	i = g->win.y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < (int)g->win.x)
		{
			color = get_color(&g->img, j, i);
			if (write(fd, &color, 4) < 0)
				cub_exit(g, -1, "File writing error!");
			j++;
		}
		i--;
	}
}

void			cub_bmp_header(t_g *g, int fd)
{
	int		header_info_size;
	int		plane_nbr;
	int		o_count;
	int		bpp;

	header_info_size = 40;
	plane_nbr = 1;
	bpp = 32;
	write(fd, &header_info_size, 4);
	write(fd, &g->win.x, 4);
	write(fd, &g->win.y, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &bpp, 2);
	o_count = 0;
	while (o_count < 24)
	{
		write(fd, "\0", 1);
		o_count++;
	}
}

int				cub_bmp(t_g *g)
{
	int		fd;
	int		file_size;
	int		first_pix;

	if ((fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755)) < 0)
		cub_exit(g, -1, "File open error!");
	g->img.img = mlx_new_image(g->mlx, g->win.x, g->win.y);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bpp,
		&g->img.line_length, &g->img.endian);
	cub_draw(g);
	file_size = 54 + g->win.x * g->win.y * 4;
	first_pix = 54;
	write(fd, "BM", 2);
	write(fd, (char*)&file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	cub_bmp_header(g, fd);
	cub_bitmap(g, fd);
	close(fd);
}
