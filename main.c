/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/09/10 20:23:23 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + y * data->img.line_length + x * (data->img.bits_per_pixel / 8);
	*(unsigned int*)dst = color;
}

void	draw_rect(t_data *data, int off_x, int off_y, uint32_t color)
{
	int i;
	int j;

	i = 0;
	while (i < data->rect.x)
	{
		j = 0;
		while (j < data->rect.y)
		{
			cub_pixel_put(data, j + off_x, i + off_y, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int i;
	int j;
	uint32_t color;

	i = 0;
	color = 0x32BFE6;
	while (data->map.tab[i])
	{
		j = 0;
		while (data->map.tab[i][j])
		{
			if (data->map.tab[i][j] == '1')
				draw_rect(data, j * data->rect.x, i * data->rect.y, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data)
{
	uint32_t color;

	color = 0xE2F029;
	draw_rect(data, (int)(data->player.x * data->rect.x - data->rect.x / 2), (int)(data->player.y * data->rect.y - data->rect.y / 2), color);
}

int		render_next_frame(t_data *data)
{
	draw_map(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx.ptr, data->win.ptr, data->img.img, 0, 0);
	mlx_do_sync(data->mlx.ptr);
	return (data->error);
}

int		close_game(t_data *data)
{
	exit(0);
	return (data->error);
}

void	cub_start(t_data *data)
{
	data->win.ptr = mlx_new_window(data->mlx.ptr, data->win.x, data->win.y, "cub2d");
	data->img.img = mlx_new_image(data->mlx.ptr, data->win.x, data->win.y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
								&data->img.endian);
	mlx_loop_hook(data->mlx.ptr, render_next_frame, data);
	mlx_hook(data->win.ptr, 17, 1L << 17, close_game, data);
	mlx_loop(data->mlx.ptr);
}

void	cub_init(char *cub)
{
	t_data		data;

	ft_bzero(&data, sizeof(data));
	data.texture.ceiling = NONE;
	data.texture.floor = NONE;
	data.mlx.ptr = mlx_init();
	data.rect.x = 45;
	data.rect.y = 45;
	cub_parse(cub, &data);
	cub_make_sqr_map(&data);
	cub_set_player(&data);
	cub_check_map(&data);
	cub_start(&data);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		cub_init(av[1]);
	else if (ac == 2)
		cub_init(av[1]);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
