/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 01:45:34 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 19:28:44 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		cub_parse_resolution(t_g *g, char *line, int *i)
{
	if (g->win.x != 0 || g->win.y != 0)
		cub_exit(g, -1, "Resolution setting error!");
	(*i)++;
	g->win.x = ft_atoi_i(line, i);
	g->win.y = ft_atoi_i(line, i);
	if (g->win.x > 2560)
		g->win.x = 2560;
	if (g->win.y > 1440)
		g->win.y = 1440;
	(*i) += ft_num_len(line);
	cub_skip_spaces(line, i);
	if (g->win.x <= 0 || g->win.y <= 0 || line[*i])
		cub_exit(g, -1, "Incorrect resolution value!");
}

static void		cub_parse_color(t_g *game, unsigned int *color,
								char *line, int *i)
{
	int		r;
	int		g;
	int		b;
	int		temp;

	if (*color != NONE)
		cub_exit(game, -1, "Color setting error!");
	(*i)++;
	temp = *i;
	r = ft_atoi_i(line, i);
	if (temp == *i || line[*i] != ',')
		cub_exit(game, -1, "Color field is empty");
	(*i)++;
	temp = *i;
	g = ft_atoi_i(line, i);
	if (temp == *i || line[*i] != ',')
		cub_exit(game, -1, "Color field is empty");
	(*i)++;
	temp = *i;
	b = ft_atoi_i(line, i);
	if (cub_skip_spaces(line, i) && temp == *i)
		cub_exit(game, -1, "Color field is empty");
	if (line[*i] || r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		cub_exit(game, -1, "Incorrect color value error!");
	*color = r * 256 * 256 + g * 256 + b;
}

static void		cub_parse_line(t_g *g, char *line)
{
	int i;

	i = 0;
	if (cub_skip_spaces(line, &i) && !line)
		return ;
	if (g->map.is_parsing || line[i] == '1')
		cub_parse_map(g, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		cub_parse_resolution(g, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		cub_parse_texture(g, &(g->n), line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		cub_parse_texture(g, &(g->s), line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		cub_parse_texture(g, &(g->w), line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		cub_parse_texture(g, &(g->e), line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		cub_parse_texture(g, &(g->sp), line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ' && (g->color |= 1))
		cub_parse_color(g, &(g->floor), line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ' && (g->color |= 2))
		cub_parse_color(g, &(g->ceiling), line, &i);
	if (cub_skip_spaces(line, &i) && line[i] != '\0')
		cub_exit(g, -1, "File parse error!");
}

static void		cub_sprites_arr(t_g *g)
{
	int			i;

	i = 0;
	if (!g->sprite_lst)
		return ;
	if (!(g->sprites = malloc(sizeof(t_sprite*) * (g->spr_cnt + 1))))
		cub_exit(g, -1, "Malloc error!");
	while (g->sprite_lst)
	{
		g->sprites[i] = (t_sprite*)ft_lstpop_left(&g->sprite_lst);
		i++;
	}
	g->sprites[i] = 0;
}

void			cub_parse(char *file, t_g *g)
{
	char	*line;
	int		fd;
	int		r;

	r = 1;
	errno = 0;
	if (!cub_check_ending(file, "cub") ||
		(fd = open(file, O_RDONLY)) == -1 || errno)
		cub_exit(g, -1, "File open error!");
	while (r == 1)
	{
		if ((r = get_next_line(fd, &line)) == 1 || r == 0)
		{
			cub_parse_line(g, line);
			free(line);
		}
	}
	close(fd);
	if (!g->map.x || !g->map.y || !g->map.tab)
		cub_exit(g, -1, "Not all params setted");
	if (!(g->x_dists = malloc(sizeof(float) * g->win.x)))
		cub_exit(g, -1, "Malloc error!");
	cub_sprites_arr(g);
	if (r < 0)
		cub_exit(g, -1, "File read error!");
}
