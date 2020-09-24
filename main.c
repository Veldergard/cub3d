/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 18:14:54 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * data->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	int j;

	if (!(s = malloc(data->map.x + 1)))
		return (NULL);
	j = 0;
	while (data->map.tab[i][j])
	{
		s[j] = data->map.tab[i][j];
		j++;
	}
	while (j < data->map.x)
	{
		s[j] = ' ';
		j++;
	}
	s[data->map.x] = 0;
}

int		cub_make_sqr_map(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->map.tab[i])
	{
		if (ft_strlen(data->map.tab[i]) != data->map.x)
		{
			temp = data->map.tab[i];
			if (!(data->map.tab[i] = cub_make_str(data, i)))
			{
				data->map.tab[i] = temp;
				return (0);
			}
			free(temp);
		}
		i++;
	}
	return (1);
}

void	cub_set_dir(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player.chr = 'E';
		data->player.dir = 0;
	}
	else if (c == 'N')
	{
		data->player.chr = 'N';
		data->player.dir = 0.5;
	}
	else if (c == 'W')
	{
		data->player.chr = 'W';
		data->player.dir = 1;
	}
	else if (c == 'S')
	{
		data->player.chr = 'S';
		data->player.dir = 1.5;
	}
}

int		cub_set_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map.tab[i])
	{
		j = 0;
		while (data->map.tab[i][j])
		{
			if (ft_strchr("NSWE", data->map.tab[i][j]))
			{
				if (data->player.chr)
					return (0);
				data->player.x = j;
				data->player.y = i;
				cub_set_dir(data, data->map.tab[i][j]);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		cub_check_map(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (data->map.tab[++i])
	{
		j = -1;
		while (data->map.tab[i][++j])
		{
			if (data->map.tab[i][j] == ' ')
			{
				if ((j > 0 && (data->map.tab[i][j - 1] != ' ' ||
				data->map.tab[i][j - 1] != '1')) ||
				(data->map.tab[i][j + 1] != ' ' ||	data->map.tab[i][j + 1] != 0
				|| data->map.tab[i][j + 1] != '1') || (data->map.tab[i + 1] &&
				(data->map.tab[i + 1][j] != '1' ||
				data->map.tab[i + 1][j] != ' ')) || i > 0 &&
				(data->map.tab[i - 1][j] != '1' ||
				data->map.tab[i - 1][j] != ' ')))
					return (0);
			}
		}
	}
	return (1);
}

void	cub_init(char *cub)
{
	t_data		data;

	ft_bzero(&data, sizeof(data));
	data.texture.ceiling = NONE;
	data.texture.floor = NONE;
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
