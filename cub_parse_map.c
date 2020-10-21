/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:37:21 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 16:15:50 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		cub_slablen(char *line)
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

static int		cub_add_sprite(t_g *g, int *i, char *line)
{
	t_sprite	*sp;
	t_list		*sp_node;

	if (line[*i] == 2)
	{
		g->spr_cnt += 1;
		if (!(sp = malloc(sizeof(t_sprite))))
		{
			return (0);
		}
		sp->x = (*i + 0.5) * CUB_SIZE;
		sp->y = (g->map.y + 0.5) * CUB_SIZE;
		if (!(sp_node = ft_lstnew(sp)))
		{
			free(sp);
			return (0);
		}
		ft_lstadd_back(&(g->sprite_lst), sp_node);
	}
	return (1);
}

static int		cub_check_map_chr(char *line, int *i)
{
	if (line[*i] == '0' || line[*i] == '1' || line[*i] == 'N'
		|| line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'
		|| line[*i] == ' ' || line[*i] == '2')
		return (1);
	return (0);
}

static char		*cub_slab(t_g *g, char *line, int *i)
{
	char		*slab;
	int			j;

	if (!(slab = malloc(sizeof(char) * (cub_slablen(line) + 1))))
		return (NULL);
	j = 0;
	*i = -1;
	while (line[++(*i)])
	{
		if (!(cub_add_sprite(g, i, line)))
		{
			free(slab);
			return (NULL);
		}
		if (cub_check_map_chr(line, i))
			slab[j++] = line[*i];
		else
		{
			free(slab);
			return (NULL);
		}
	}
	g->map.x = j > g->map.x ? j : g->map.x;
	slab[j] = '\0';
	return (slab);
}

void			cub_parse_map(t_g *g, char *line, int *i)
{
	char	**tmp;
	int		j;

	if (!(tmp = malloc(sizeof(char*) * (g->map.y + 2))))
		cub_exit(g, -1, "Malloc error!");
	j = -1;
	while (++j < g->map.y)
		tmp[j] = g->map.tab[j];
	if ((tmp[g->map.y] = cub_slab(g, line, i)) == NULL)
	{
		free(tmp);
		cub_exit(g, -1, "Malloc error!");
	}
	tmp[g->map.y + 1] = NULL;
	if (g->map.y > 0)
		free(g->map.tab);
	g->map.tab = tmp;
	g->map.y++;
}
