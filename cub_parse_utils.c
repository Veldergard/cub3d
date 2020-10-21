/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:39:37 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:42:09 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				cub_skip_spaces(char *line, int *i)
{
	while (line && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	return (1);
}

static int		cub_check_ending(char *file, char *ext)
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

static void		cub_xpm(t_g *g, t_img *adr, char *file)
{
	int		fd;

	if (!cub_check_ending(file, "xpm"))
	{
		free(file);
		cub_exit(g, -1, "File type error!");
	}
	errno = 0;
	if ((fd = open(file, O_RDONLY)) == -1 || errno)
	{
		free(file);
		cub_exit(g, -1, "File not found!");
	}
	close(fd);
	adr->img = mlx_xpm_file_to_image(g->mlx, file, &(adr->wdt), &(adr->hgt));
	if (adr->img == NULL)
	{
		free(file);
		cub_exit(g, -1, "Texture setting error!");
	}
	adr->addr = mlx_get_data_addr(adr->img, &(adr->bpp), &(adr->line_length),
		&(adr->endian));
}

void			cub_parse_texture(t_g *g, t_img *adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (adr->addr)
		cub_exit(g, -1, "Texture setting error!");
	(*i) += 2;
	cub_skip_spaces(line, i);
	j = *i;
	while (line[j] != ' ' && line[j])
		j++;
	if (!(file = malloc(j - (*i) + 1)))
		cub_exit(g, -1, "Malloc error!");
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	cub_xpm(g, adr, file);
	free(file);
}

int				cub_check_params(t_g *g)
{
	if (!g->win.x || !g->win.y || !g->map.tab || !g->map.x || !g->map.y)
		return (0);
	if (!g->sp.addr || !g->n.addr || !g->s.addr || !g->e.addr || !g->w.addr)
		return (0);
	if (g->color != 3)
		return (0);
	return (1);
}
