/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/27 01:42:39 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(char *cub)
{
	t_data		data;
	t_window	window;
	t_texture	texture;
	t_map		map;

	window.x = 0;
	window.y = 0;
	data.window = window;
	texture.n = NULL;
	texture.s = NULL;
	texture.e = NULL;
	texture.w = NULL;
	texture.sp = NULL;
	texture.ceiling = NONE;
	texture.floor = NONE;
	data.texture = texture;
	data.error = 0;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	map.tab = NULL;
	data.map = map;
	cub_parse(cub, &data);
	int i = 0;
	while (data.map.tab[i])
	{
		printf("%s\n", data.map.tab[i++]);
	}
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_strcmp(av[2], "--save"))
		ft_init(av[1]);
	else if (ac == 2)
		ft_init(av[1]);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
