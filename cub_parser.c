/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 01:45:34 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 18:15:07 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_spaces(char *line, int *i)
{
	while (line && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
	return (1);
}

int		parse_resolution(t_data *data, char *line, int *i)
{
	if (data->window.x != 0 || data->window.y != 0)
		return (-3);
	(*i)++;
	data->window.x = ft_atoi_i(line, i);
	data->window.y = ft_atoi_i(line, i);
	if (data->window.x > 4096)
		data->window.x = 4096;
	if (data->window.y > 2304)
		data->window.y = 2304;
	(*i) += ft_num_len(line);
	skip_spaces(line, i);
	if (data->window.x <= 0 || data->window.y <= 0 || line[*i])
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

int		ft_xpm(t_data *data, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];

	if (!check_ending(file, "xpm"))
		return (-1);
	errno = 0;
	if ((fd = open(file, O_RDONLY)) == -1 || errno)
		return (-1);
	close(fd);
	// img = mlx_xpm_file_to_image(data->mlx.ptr, file, &tab[0], &tab[1]);
	// if (img == NULL || tab[0] != 64 || tab[1] != 64)
		// return (-1);
	// *adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	// free(img);
	return (0);
}

int		parse_texture(t_data *data, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr)
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
	j = ft_xpm(data, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

int		ft_slablen(t_data *data, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
			count++;
		else if (line[i] == 'E')
			count++;
		i++;
	}
	if (data->map.x != 0 && data->map.x != count)
		return (-1);
	return (count);
}

char	*ft_slab(t_data *data, char *line, int *i)
{
	char	*slab;
	int		j;

	if (!(slab = malloc(sizeof(char) * (ft_slablen(data, line) + 1))))
		return (NULL);
	j = 0;
	while (line[*i])
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			slab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			slab[j++] = line[*i];
			data->map.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int		parse_map(t_data *data, char *line, int *i)
{
	char	**tmp;
	int		j;

	data->error = 1;
	if (!(tmp = malloc(sizeof(char*) * (data->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < data->map.y)
		tmp[j] = data->map.tab[j];
	if ((tmp[data->map.y] = ft_slab(data, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[data->map.y + 1] = NULL;
	if (data->map.y > 0)
		free(data->map.tab);
	data->map.tab = tmp;
	data->map.y++;
	if ((data->map.x = ft_slablen(data, line)) == -1)
		return (-13);
	return (0);
}

static int		parse_line(t_data *data, char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i);
	if (!line || !*line)
		return (0);
	if (line[i] == '1')
		data->error = parse_map(data, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		data->error = parse_resolution(data, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		data->error = parse_texture(data, &(data->texture.n), line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		data->error = parse_texture(data, &(data->texture.s), line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		data->error = parse_texture(data, &(data->texture.w), line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		data->error = parse_texture(data, &(data->texture.e), line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		data->error = parse_texture(data, &(data->texture.sp), line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		data->error = parse_color(&(data->texture.floor), line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		data->error = parse_color(&(data->texture.ceiling), line, &i);
	if (skip_spaces(line, &i) && data->error == 0 && line[i] != '\0')
		data->error = -10;
	return (data->error < 0 ? -1 : 0);
}

int				cub_parse(char *file, t_data *data)
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
		if (r == 1 && parse_line(data, line) == -1)
			r = -2;
		free(line);
	}
	close(fd);
	if (r < 0)
		return (0);
	return (1);
}
