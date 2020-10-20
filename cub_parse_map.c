/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:37:21 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/20 19:37:42 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			cub_slablen(char *line)
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

char		*cub_slab(t_g *g, char *line, int *i)
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
			{
				free(slab);
				return (NULL);
			}
			sp->x = (*i + 0.5) * CUB_SIZE;
			sp->y = (g->map.y + 0.5) * CUB_SIZE;
			if (!(sp_node = ft_lstnew(sp)))
			{
				free(sp);
				free(slab);
				return (NULL);
			}
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

void		parse_map(t_g *g, char *line, int *i)
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
