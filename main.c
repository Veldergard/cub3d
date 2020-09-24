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

<<<<<<< HEAD
float	distance(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	cub_draw_rays_3D(t_data *data)
{
	int		r;
	int		ray;
	int		depth_of_field;
	int		x_offset;
	int		y_offset;
	int		map_x;
	int		map_y;
	int		map;
	float	arc_tan;
	float	nTan;
	float	ray_x;
	float	ray_y;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	disH;
	float	disV;
	float	hx;
	float	vx;
	float	hy;
	float	vy;

	map = data->map.tab;
	px = data->player.x;
	py = data->player.y;
	r = 0;
	ray = data->player.dir;
	while (r < 1)
	{
		// Horizontal
		depth_of_field = 0;
		disH = 1000000;
		hx = px;
		hy = py;
		arc_tan = -1 / tan(ray);
		if (ray > PI)
		{
			ray_y = (((int)py >> 6) << 6) - 0.0001;
			ray_x = (py - ray_y) * arc_tan + px;
			y_offset = -64;
			x_offset = -y_offset * arc_tan;
		}
		else if (ray < PI)
		{
			ray_y = (((int)py >> 6) << 6) + 64;
			ray_x = (py - ray_y) * arc_tan + px;
			y_offset = 64;
			x_offset = -y_offset * arc_tan;
		}
		else if (ray == 0 || ray == PI)
		{
			ray_x = px;
			ray_y = py;
			depth_of_field = 8;
		}
		while (depth_of_field < 8)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_x) >> 6;
			mp = map_y * data->map.x + map_x;
			if ((map_x > 0 || map_y > 0) &&
				map_y * data->map.x + map_x < data->map.x * data->map.y &&
				data->map.tab[map_y][map_x] == 1)
			{
				hx = rx;
				hy = ry;
				disH = distance(px, py, hx, hy, ra);
				depth_of_field = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		// Vertical
		depth_of_field = 0;
		disV = 1000000;
		vx = px;
		vy = py;
		nTan = -tan(ray);
		if (ray > PI2 && ray < PI3)
		{
			ray_x = (((int)px >> 6) << 6) - 0.0001;
			ray_y = (px - ray_x) * nTan + py;
			x_offset = -64;
			y_offset = -x_offset * nTan;
		}
		else if (ray < PI2 || ray > PI3)
		{
			ray_x = (((int)px >> 6) << 6) + 64;
			ray_y = (px - ray_x) * nTan + py;
			x_offset = 64;
			y_offset = -x_offset * nTan;
		}
		else if (ray == 0 || ray == PI)
		{
			ray_x = px;
			ray_y = py;
			depth_of_field = 8;
		}
		while (depth_of_field < 8)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_x) >> 6;
			if ((map_x > 0 || map_y > 0) &&
				map_y * data->map.x + map_x < data->map.x * data->map.y &&
				data->map.tab[map_y][map_x] == 1)
			{
				vx = rx;
				vy = ry;
				disV = distance(px, py, vx, vy, ra);
				depth_of_field = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
		}
		r++;
	}
}

int		cub_render_next_frame(t_data *data)
{
}

void	cub_start(t_data *data)
{
	void *mlx;
	void *mlx_win;
	t_img img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	cub_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop_hook(mlx, cub_render_next_frame, data);
	mlx_loop(mlx);
}

char	*cub_make_str(t_data *data, int i)
{
	char *s;
=======
void	draw_rect(t_data *data, int off_x, int off_y, uint32_t color)
{
	int i;
>>>>>>> 3563cacaa2ea28e4840e854c53c84dfd66de2a28
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
