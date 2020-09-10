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

int		render_next_frame(t_data *data)
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
	mlx_loop_hook(mlx, render_next_frame, data);
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
