/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:35:12 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/08 18:30:25 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y, t_path *path)
{
    if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '\0')
        return;
    if (map[y][x] == '1' || map[y][x] == 'V')
        return;
    if (map[y][x] == 'C')
        path->collected++;
    else if (map[y][x] == 'E')
        path->exit_found = 1;
    map[y][x] = 'V';
    flood_fill(map, x + 1, y, path);
    flood_fill(map, x - 1, y, path);
    flood_fill(map, x, y + 1, path);
    flood_fill(map, x, y - 1, path);
}

static void	find_player_position(char **map, int *x, int *y)
{
    int i = 0, j;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
                *x = j;
                *y = i;
                return;
            }
            j++;
        }
        i++;
    }
}

void check_path(t_map *map)
{
    char	**copy;
    int		x;
    int		y;
	t_path	path;

	copy = ft_copy_2d(map->game_map);
	path.collected = 0;
	path.total_collectibles = map->collect;
	path.exit_found = 0;
	find_player_position(copy, &x, &y);
	flood_fill(copy, x, y, &path);
	ft_free_2d((void **)copy);
	if (path.collected != path.total_collectibles)
		map_error("Not all collectibles are reachable!\n", map);
	if (!path.exit_found)
		map_error("Exit is not reachable!\n", map);
}
