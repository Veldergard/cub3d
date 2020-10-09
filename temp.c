/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 18:15:37 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/09 18:15:39 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	cub_draw_walls(t_g *g)
{
	int		r;
	int		depth_of_field;
	int		x_offset;
	int		y_offset;
	int		map_x;
	int		map_y;
	float	ray;
	float	arc_tan;
	float	not_tan;
	float	ray_x;
	float	ray_y;
	float	disH;
	float	disV;
	float	dist;
	float	lineH;
	float	ca;
	float	lineO;
	float	step;

	r = 0;
	ray = g->player.dir - DR * 30;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray > 2 * PI ? ray - 2 * PI : ray;
	step = 60. * DR / (float)g->win.x;
	while (r < g->win.x)
	{
		// Vertical
		depth_of_field = 0;
		disV = 1000000;
		not_tan = -tan(ray);
		if (ray > PI2 && ray < PI3)
		{
			ray_x = (((int)g->player.x >> 6) << 6) - 0.0001;
			ray_y = (g->player.x - ray_x) * not_tan + g->player.y;
			x_offset = -64;
			y_offset = -x_offset * not_tan;
		}
		else if (ray < PI2 || ray > PI3)
		{
			ray_x = (((int)g->player.x >> 6) << 6) + 64;
			ray_y = (g->player.x - ray_x) * not_tan + g->player.y;
			x_offset = 64;
			y_offset = -x_offset * not_tan;
		}
		else
		{
			ray_x = g->player.x;
			ray_y = g->player.y;
			depth_of_field = DOF;
		}
		while (depth_of_field < DOF)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_y) >> 6;
			if (map_x >= 0 && map_y >= 0 &&
				map_y < g->map.y && map_x < g->map.x &&
				g->map.tab[map_y][map_x] == '1')
			{
				disV = cub_dist(g->player.x, g->player.y, ray_x, ray_y);
				depth_of_field = DOF;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		// Horizontal
		depth_of_field = 0;
		disH = 1000000;
		arc_tan = -1 / tan(ray);
		if (ray > PI)
		{
			ray_y = (((int)g->player.y >> 6) << 6) - 0.0001;
			ray_x = (g->player.y - ray_y) * arc_tan + g->player.x;
			y_offset = -64;
			x_offset = -y_offset * arc_tan;
		}
		else if (ray < PI)
		{
			ray_y = (((int)g->player.y >> 6) << 6) + 64;
			ray_x = (g->player.y - ray_y) * arc_tan + g->player.x;
			y_offset = 64;
			x_offset = -y_offset * arc_tan;
		}
		else
		{
			ray_x = g->player.x;
			ray_y = g->player.y;
			depth_of_field = DOF;
		}
		while (depth_of_field < DOF)
		{
			map_x = (int)(ray_x) >> 6;
			map_y = (int)(ray_y) >> 6;
			if (map_x >= 0 && map_y >= 0 &&
				map_y < g->map.y && map_x < g->map.x &&
				g->map.tab[map_y][map_x] == '1')
			{
				disH = cub_dist(g->player.x, g->player.y, ray_x, ray_y);
				depth_of_field = DOF;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			}
		}
		if (disV < disH)
			dist = disV;
		else
			dist = disH;
		ca = g->player.dir - ray;
		ca = ca < 0 ? ca + 2 * PI : ca;
		ca = ca > 2 * PI ? ca - 2 * PI : ca;
		dist = dist * cos(ca);
		lineH = (CUB_SIZE * g->win.y) / dist;
		lineH = lineH > g->win.y ? g->win.y : lineH;
		lineO = (int)(g->win.y - lineH) / 2;
		printf("lineH = %f dist = %f disV = %f disH = %f\n", lineH, dist, disV, disH);
		cub_draw_line(g, r, lineO, lineH + lineO);
		ray += step;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray > 2 * PI ? ray - 2 * PI : ray;
		r++;
	}
}
