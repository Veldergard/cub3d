/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 04:05:18 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/21 17:12:11 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		separate_line_with_endline(char **line, char **remainder)
{
	*line = ft_strdup(*remainder);
	free(*remainder);
	*remainder = NULL;
	if (!(*line))
		return (-1);
	return (0);
}

int		separate_line(char **p_n, char **line, char **remainder)
{
	char		*temp;

	*p_n = *p_n ? *p_n : ft_strchr(*remainder, '\0');
	if (**p_n == '\n')
	{
		**p_n = '\0';
		if (!(*line = ft_strdup(*remainder)))
		{
			free(*remainder);
			*remainder = NULL;
			return (-1);
		}
		temp = *remainder;
		if (((*p_n)[1] != '\0' && !((*remainder) = ft_strdup(*p_n + 1)))
			|| (*p_n)[1] == '\0')
			*remainder = NULL;
		free(temp);
		return (1);
	}
	return (separate_line_with_endline(line, remainder));
}

int		check_read(char **p_n, char **line, char **remainder, int readed)
{
	if (readed < 0 && (!(*remainder) || (*remainder)[0] == 0))
		return (-1);
	else if (readed == 0 && (!(*remainder) || (*remainder)[0] == 0))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (separate_line(p_n, line, remainder));
}

int		get_next_line(int fd, char **line)
{
	static char		*remainder = NULL;
	char			*temp;
	char			buf[BUFFER_SIZE + 1];
	int				readed;
	char			*p_n;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	p_n = remainder ? ft_strchr(remainder, '\n') : NULL;
	readed = 0;
	while (!p_n && (readed = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readed] = '\0';
		if (!remainder && (!(remainder = ft_strdup(""))))
			return (-1);
		temp = remainder;
		remainder = ft_strjoin(remainder, buf);
		free(temp);
		if (!remainder && !(remainder = NULL))
			return (-1);
		if ((p_n = ft_strchr(remainder, '\n')))
			break ;
	}
	return (check_read(&p_n, line, &remainder, readed));
}
