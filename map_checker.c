/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:58:33 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/13 17:58:55 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (s);
}

int		cub_make_sqr_map(t_g *g)
{
	int		i;
	char	*temp;

	i = 0;
	while (g->map.tab[i])
	{
		if ((int)ft_strlen(g->map.tab[i]) != g->map.x)
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
		g->player.dir = PI2;
	}
	else if (c == 'W')
	{
		g->player.chr = 'W';
		g->player.dir = PI;
	}
	else if (c == 'S')
	{
		g->player.chr = 'S';
		g->player.dir = PI3;
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
				g->player.x = (j + 0.5) * 64;
				g->player.y = (i + 0.5) * 64;
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
				g->map.tab[i + 1][j] != ' ')) || (i > 0 &&
				(g->map.tab[i - 1][j] != '1' ||
				g->map.tab[i - 1][j] != ' ')))
					return (0);
			}
		}
	}
	return (1);
}
