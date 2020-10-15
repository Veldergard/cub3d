/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 01:45:34 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/15 19:13:04 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_spaces(char *line, int *i)
{
	while (line && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	return (1);
}

int		parse_resolution(t_g *g, char *line, int *i)
{
	if (g->win.x != 0 || g->win.y != 0)
		return (-3);
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
		return (-4);
	return (0);
}

int		parse_color(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_atoi_i(line, i);
	(*i)++;
	g = ft_atoi_i(line, i);
	(*i)++;
	b = ft_atoi_i(line, i);
	skip_spaces(line, i);
	if (line[*i] || r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

int		check_ending(char *file, char *ext)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if ((i > 4 && file[i - 1] == ext[2] && file[i - 2] == ext[1])
		&& (file[i - 3] == ext[0] && file[i - 4] == '.'))
		return (1);
	return (0);
}

int		cub_xpm(t_g *g, t_img *adr, char *file)
{
	int		fd;

	if (!check_ending(file, "xpm"))
		return (-1);
	errno = 0;
	if ((fd = open(file, O_RDONLY)) == -1 || errno)
		return (-1);
	close(fd);
	adr->img = mlx_xpm_file_to_image(g->mlx, file, &(adr->wdt), &(adr->hgt));
	if (adr->img == NULL || adr->wdt != 64 || adr->hgt != 64)
		return (-1);
	adr->addr = mlx_get_data_addr(adr->img, &(adr->bpp), &(adr->line_length), &(adr->endian));
	return (0);
}

int		parse_texture(t_g *g, t_img *adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (adr->addr)
		return (-7);
	(*i) += 2;
	skip_spaces(line, i);
	j = *i;
	while (line[j] != ' ' && line[j])
		j++;
	if (!(file = malloc(j - (*i) + 1)))
		return (-8);
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = cub_xpm(g, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

int		cub_slablen(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == ' '
		|| line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			count++;
		i++;
	}
	return (count);
}

char	*cub_slab(t_g *g, char *line, int *i)
{
	char		*slab;
	int			j;
	t_sprite	*sp;
	t_list		*sp_node;


	if (!(slab = malloc(sizeof(char) * (cub_slablen(line) + 1))))
		return (NULL);
	j = 0;
	*i = 0;
	while (line[*i])
	{
		if (line[*i] == '2')
		{
			g->spr_cnt += 1;
			if (!(sp = malloc(sizeof(t_sprite))))
				return (NULL);
			sp->x = *i;
			sp->y = g->map.y;
			if (!(sp_node = ft_lstnew(sp)))
				return (NULL);
			ft_lstadd_back(&(g->sprite_lst), sp_node);
		}
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == 'N'
		|| line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'
		|| line[*i] == ' ' || line[*i] == '2')
			slab[j++] = line[*i];
		else
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	if (j > g->map.x)
		g->map.x = j;
	slab[j] = '\0';
	return (slab);
}

int		parse_map(t_g *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	g->error = 1;
	if (!(tmp = malloc(sizeof(char*) * (g->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < g->map.y)
		tmp[j] = g->map.tab[j];
	if ((tmp[g->map.y] = cub_slab(g, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[g->map.y + 1] = NULL;
	if (g->map.y > 0)
		free(g->map.tab);
	g->map.tab = tmp;
	g->map.y++;
	return (0);
}

static int		parse_line(t_g *g, char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i);
	if (!line || !*line)
		return (0);
	if (line[i] == '1')
		g->error = parse_map(g, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		g->error = parse_resolution(g, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		g->error = parse_texture(g, &(g->n), line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		g->error = parse_texture(g, &(g->s), line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		g->error = parse_texture(g, &(g->w), line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		g->error = parse_texture(g, &(g->e), line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		g->error = parse_texture(g, &(g->sp), line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		g->error = parse_color(&(g->floor), line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		g->error = parse_color(&(g->ceiling), line, &i);
	if (skip_spaces(line, &i) && g->error == 0 && line[i] != '\0')
		g->error = -10;
	return (g->error < 0 ? -1 : 0);
}

int				cub_sprites_arr(t_g *g)
{
	int			i;
	t_sprite	*temp;

	i = 0;
	if (!g->sprite_lst)
		return (1);
	if (!(g->sprites = malloc(sizeof(t_sprite) * g->spr_cnt + 1)))
		return (-1);
	while (1)
	{
		temp = (t_sprite*)ft_lstpop_left(&g->sprite_lst);

		free(temp);
	}
}

int				cub_parse(char *file, t_g *g)
{
	char	*line;
	int		fd;
	int		r;

	r = 1;
	errno = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1 || errno)
		return (0);
	while (r == 1)
	{
		r = get_next_line(fd, &line);
		if (r == 1 && parse_line(g, line) == -1)
			r = -2;
		free(line);
	}
	close(fd);
	cub_sprites_arr(g);
	if (r < 0)
		return (0);
	return (1);
}
