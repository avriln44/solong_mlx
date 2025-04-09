/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:10:44 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/08 17:50:32 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_rectangle(t_map *map)
{
	int		i;
	size_t	len_line;

	i = 0;
	len_line = ft_strlen(map->game_map[0]);
	while (map->game_map[i])
	{
		if (len_line != ft_strlen(map->game_map[i]))
			map_error("The map has to be a rectangle!\n", map);
		len_line = ft_strlen(map->game_map[i]);
		i++;
	}
}

static void	check_objects(t_map *map)
{
	if (map->exit < 1)
		map_error("There is no exit!\n", map);
	else if (map->exit > 1)
		map_error("There should be only one exit!\n", map);
	else if (map->player < 1)
		map_error("There is no player!\n", map);
	else if (map->player > 1)
		map_error("There should be only 1 player!\n", map);
	else if (map->collect < 1)
		map_error("There should be at least 1 collectible!\n", map);
}

static void	check_border(t_map *map)
{
	int row;
	int col;

	row = 0;
	while (row < map->length)
	{
		if (map->game_map[0][row] != '1')
			map_error("Map must be surrounded by walls!\n", map);
		if (map->game_map[map->width - 1][row] != '1')
			map_error("Map must be surrounded by walls!\n", map);
		row++;
	}
	col = 0;
	while (col < map->width)
	{
		if (map->game_map[col][0] != '1')
			map_error("Map must be surrounded by walls!\n", map);
		if (map->game_map[col][map->length - 1] != '1')
			map_error("Map must be surrounded by walls!\n", map);
		col++;
	}
}

void	map_validation(t_map *map)
{
	check_border(map);
	check_objects(map);
	check_rectangle(map);
	check_path(map);
}
