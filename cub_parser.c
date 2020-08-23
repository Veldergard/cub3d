/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 01:45:34 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/23 03:37:08 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		skip_spaces(char *line, int *i)
{
	while (line && *line && (*line >= 9 && *line <= 13 || *line == 32))
		(*i)++;
}

static int		parse_line(t_data *data, char *line)
{
	int i;

	i = 0;
	skip_spaces(line, &i);
	if (!line || !*line)
		return (0);
	if (line[i] == 'R' && line[i + 1] == ' ')
		pass;
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		pass;
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		pass;
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		pass;
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		pass;
	else if (line[i] == 'S' && line[i + 1] == ' ')
		pass;
	else if (line[i] == 'F' && line[i + 1] == ' ')
		pass;
	else if (line[i] == 'C' && line[i + 1] == ' ')
		pass;

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
