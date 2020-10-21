/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 01:45:34 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 15:22:44 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		parse_resolution(t_g *g, char *line, int *i)
{
	if (g->win.x != 0 || g->win.y != 0)
		cub_exit(g, -1, "Resolution setting error!");
	(*i)++;
	g->win.x = ft_atoi_i(line, i);
	g->win.y = ft_atoi_i(line, i);
	if (g->win.x > 16000)
		g->win.x = 16000;
	if (g->win.y > 16000)
		g->win.y = 16000;
	(*i) += ft_num_len(line);
	skip_spaces(line, i);
	if (g->win.x <= 0 || g->win.y <= 0 || line[*i])
		cub_exit(g, -1, "Incorrect resolution value!");
}

void		parse_color(t_g *game, unsigned int *color, char *line, int *i)
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
	if (temp == *i || line[*i] != ',')
		cub_exit(game, -1, "Color field is empty");
	skip_spaces(line, i);
	if (line[*i] || r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		cub_exit(game, -1, "Incorrect color value error!");
	*color = r * 256 * 256 + g * 256 + b;
}

void		parse_line(t_g *g, char *line)
{
	int i;

	i = 0;
	if (skip_spaces(line, &i) && (!line || !*line))
		return ;
	if (line[i] == '1')
		parse_map(g, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		parse_resolution(g, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(g, &(g->n), line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		parse_texture(g, &(g->s), line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		parse_texture(g, &(g->w), line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		parse_texture(g, &(g->e), line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		parse_texture(g, &(g->sp), line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ' && (g->color |= 1))
		parse_color(g, &(g->floor), line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ' && (g->color |= 2))
		parse_color(g, &(g->ceiling), line, &i);
	if (skip_spaces(line, &i) && line[i] != '\0')
		cub_exit(g, -1, "File parse error!");
}

void		cub_sprites_arr(t_g *g)
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

int			check_params(t_g *g)
{
	if (!g->win.x || !g->win.y || !g->map.tab || !g->map.x || !g->map.y)
		return (0);
	if (!g->sp.addr || !g->n.addr || !g->s.addr || !g->e.addr || !g->w.addr)
		return (0);
	if (g->color != 3)
		return (0);
	return (1);
}

void		cub_parse(char *file, t_g *g)
{
	char	*line;
	int		fd;
	int		r;

	r = 1;
	errno = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1 || errno)
		cub_exit(g, -1, "File open error!");
	while (r == 1)
	{
		r = get_next_line(fd, &line);
		if (r == 1 || r == 0)
		{
			parse_line(g, line);
			free(line);
		}
	}
	close(fd);
	if (!(check_params(g)))
		cub_exit(g, -1, "Not all params setted");
	if (!(g->x_dists = malloc(sizeof(float) * g->win.x)))
		cub_exit(g, -1, "Malloc error!");
	cub_sprites_arr(g);
	if (r < 0)
		cub_exit(g, -1, "File read error!");
}
