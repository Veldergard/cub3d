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

	dst = img->addr + (y * g->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	cub_dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	cub_draw(t_g *g)
{
}

void	cub_raycaster(t_g *g)
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
	float	not_tan;
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
	float	dist;
	float	lineH;

	map = g->map.tab;
	px = g->player.x;
	py = g->player.y;
	r = 0;
	ray = g->player.dir - DR * 30;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray > 2 * PI ? ray - 2 * PI : ray;
	while (r < 60)
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
			mp = map_y * g->map.x + map_x;
			if ((map_x > 0 || map_y > 0) &&
				map_y * g->map.x + map_x < g->map.x * g->map.y &&
				g->map.tab[map_y][map_x] == 1)
			{
				hx = rx;
				hy = ry;
				disH = cub_dist(px, py, hx, hy, ra);
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
		not_tan = -tan(ray);
		if (ray > PI2 && ray < PI3)
		{
			ray_x = (((int)px >> 6) << 6) - 0.0001;
			ray_y = (px - ray_x) * not_tan + py;
			x_offset = -64;
			y_offset = -x_offset * not_tan;
		}
		else if (ray < PI2 || ray > PI3)
		{
			ray_x = (((int)px >> 6) << 6) + 64;
			ray_y = (px - ray_x) * not_tan + py;
			x_offset = 64;
			y_offset = -x_offset * not_tan;
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
				map_y * g->map.x + map_x < g->map.x * g->map.y &&
				g->map.tab[map_y][map_x] == 1)
			{
				vx = rx;
				vy = ry;
				disV = cub_dist(px, py, vx, vy, ra);
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
			dist = disV;
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
			dist = disH;
		}
		float ca = g->player.dir - ray;
		ca = ca < 0 ? ca + 2 * PI : ca;
		ca = ca > 2 * PI ? ca - 2 * PI : ca;
		dist = dist * cos(ca); // fix fisheye
		lineH = (mapS * 320) / dist;
		lineH = lineH > 320 ? 320 : lineH;
		float lineO = 160 - lineH / 2; // line offset
		cub_draw(r * 8, lineO);
		cub_draw(r * 8, lineO + lineH);
		ray += DR;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray > 2 * PI ? ray - 2 * PI : ray;
		r++;
	}
}

int		cub_render_next_frame(t_g *g)
{
	cub_raycaster(g);
}

void	cub_rotate(t_g *g, double dir)
{
	g->player.dir += dir * R_SPD;
	while (g->player.dir < 0)
		g->player.dir += 2 * PI;
	while (g->player.dir > 2 * PI)
		g->player.dir -= 2 * PI;
}

void	cub_move(t_g *g, double dir)
{
	g->player.y -= dir * sin(g->player.dir) * SPEED;
	g->player.x += dir * cos(g->player.dir) * SPEED;
}

void	cub_strafe(t_g *g, double c)
{
	g->player.y += dir * cos(g->player.dir) * SPEED;
	g->player.x += dir * sin(g->player.dir) * SPEED;
}

int		cub_key(int key, t_g *g)
{
	if (key == ESC)
		cub_close(g, 1);
	else if (key == W)
		cub_move(g, 1);
	else if (key == A)
		cub_strafe(g, -1);
	else if (key == S)
		cub_move(g, -1);
	else if (key == D)
		cub_strafe(g, 1);
	else if (key == LEFT)
		cub_rotate(g, -1);
	else if (key == RIGHT)
		cub_rotate(g, 1);
	cub_render_next_frame(g);
	return (1);
}

int		cub_start(t_g *g, int bmp)
{
	g->mlx.ptr = mlx_init();
	if (bmp == 1)
		return (cub_bitmap(&g));
	g->win.ptr = mlx_new_window(g->mlx.ptr, g->win.x, g->win.y, "cub3D");
	g->img.img = mlx_new_image(g->mlx, 1920, 1080);
	g->img.addr = mlx_get_g_addr(g->img.img, &g->img.bits_per_pixel,
					&g->img.line_length, &g->img.endian);
	cub_pixel_put(&g->img, 5, 5, 0x00FF0000);
	ft_draw(&g);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, 02, 0L, cub_key, g);
	mlx_hook(mlx_win, 17, 0L, cub_close, g);
	mlx_loop(mlx);
	return (1);
}

char	*cub_make_str(t_g *g, int i)
{
	char *s;
	int j;

	if (!(s = malloc(g->map.x + 1)))
		return (NULL);
	j = 0;
	while (g->map.tab[i][j])
	{
		s[j] = g->map.tab[i][j];
		j++;
	}
	while (j < g->map.x)
	{
		s[j] = ' ';
		j++;
	}
	s[g->map.x] = 0;
}

int		cub_make_sqr_map(t_g *g)
{
	int		i;
	char	*temp;

	i = 0;
	while (g->map.tab[i])
	{
		if (ft_strlen(g->map.tab[i]) != g->map.x)
		{
			temp = g->map.tab[i];
			if (!(g->map.tab[i] = cub_make_str(g, i)))
			{
				g->map.tab[i] = temp;
				return (0);
			}
			free(temp);
		}
		i++;
	}
	return (1);
}

void	cub_set_dir(t_g *g, char c)
{
	if (c == 'E')
	{
		g->player.chr = 'E';
		g->player.dir = 0;
	}
	else if (c == 'N')
	{
		g->player.chr = 'N';
		g->player.dir = 0.5;
	}
	else if (c == 'W')
	{
		g->player.chr = 'W';
		g->player.dir = 1;
	}
	else if (c == 'S')
	{
		g->player.chr = 'S';
		g->player.dir = 1.5;
	}
}

int		cub_set_player(t_g *g)
{
	int i;
	int j;

	i = 0;
	while (g->map.tab[i])
	{
		j = 0;
		while (g->map.tab[i][j])
		{
			if (ft_strchr("NSWE", g->map.tab[i][j]))
			{
				if (g->player.chr)
					return (0);
				g->player.x = j;
				g->player.y = i;
				cub_set_dir(g, g->map.tab[i][j]);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		cub_check_map(t_g *g)
{
	int i;
	int j;

	i = -1;
	while (g->map.tab[++i])
	{
		j = -1;
		while (g->map.tab[i][++j])
		{
			if (g->map.tab[i][j] == ' ')
			{
				if ((j > 0 && (g->map.tab[i][j - 1] != ' ' ||
				g->map.tab[i][j - 1] != '1')) ||
				(g->map.tab[i][j + 1] != ' ' ||	g->map.tab[i][j + 1] != 0
				|| g->map.tab[i][j + 1] != '1') || (g->map.tab[i + 1] &&
				(g->map.tab[i + 1][j] != '1' ||
				g->map.tab[i + 1][j] != ' ')) || i > 0 &&
				(g->map.tab[i - 1][j] != '1' ||
				g->map.tab[i - 1][j] != ' ')))
					return (0);
			}
		}
	}
	return (1);
}

void	cub_init(char *cub, int bmp)
{
	t_g		g;

	ft_bzero(&g, sizeof(g));
	g.text.ceiling = NONE;
	g.text.floor = NONE;
	cub_parse(cub, &g);
	cub_make_sqr_map(&g);
	cub_set_player(&g);
	cub_check_map(&g);
	cub_start(&g);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		cub_init(av[1], 1);
	else if (ac == 2)
		cub_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
