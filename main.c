/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 23:09:11 by olaurine          #+#    #+#             */
/*   Updated: 2020/08/23 00:14:56 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int ac, char **av)
{
	t_data map;

	if (ac == 3 && ft_strcmp(av[2], "--save"))
	{
		write(1, "Game saved\n", 11);
	}
	else if (ac == 2)
	{
		ft_bzero(&map, sizeof(t_data));
		cub_parser(av[1], &data);
	}
	else
	{
		write(1, "Error\n", 6);
	}
}
