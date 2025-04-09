/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:34:01 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/08 18:47:59 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, t_path *path)
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

char	**ft_copy_2d(char **map)
{
    int		i;
    char	**copy;

    i = 0;
    while (map[i])
        i++;
    copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (map[i])
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
        {
            ft_free_2d((void **)copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

void ft_printf_fd(int fd, const char *str)
{
    write(fd, str, ft_strlen(str));
}

void ft_free_2d(void **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}