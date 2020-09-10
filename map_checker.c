/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 19:58:33 by olaurine          #+#    #+#             */
/*   Updated: 2020/09/10 20:21:30 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (s);
}

int		cub_make_sqr_map(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->map.tab[i])
	{
		if ((int)ft_strlen(data->map.tab[i]) != data->map.x)
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
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
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
				data->map.tab[i + 1][j] != ' ')) || (i > 0 &&
				(data->map.tab[i - 1][j] != '1' ||
				data->map.tab[i - 1][j] != ' ')))
					return (0);
			}
		}
	}
	return (1);
}
