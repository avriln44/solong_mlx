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

void	count_objects(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->game_map[i])
    {
        j = 0;
        while (map->game_map[i][j])
        {
            if (map->game_map[i][j] == '0')
                map->space++;
            else if (map->game_map[i][j] == 'E')
                map->exit++;
            else if (map->game_map[i][j] == 'C')
                map->collect++;
            else if (map->game_map[i][j] == 'P')
            {
                map->player++;
                map->start.row = i;
                map->start.col = j;
            }
            else if (map->game_map[i][j] != '1')
                game_map_error(0, "Error:\nInvalid character in map\n", map);
            j++;
        }
        i++;
    }
}

void	exit_solong(t_solong *solong, int32_t stt)
{
	int32_t	index;

	if (!solong)
		exit(stt);
	if (solong->map && solong->map->game_map)
		ft_free_2d((void **)solong->map->game_map);

	if (solong->image)
	{
		index = 0;
		while (index < IMG_TYPE)
		{
			if (solong->image[index])
				mlx_delete_image(solong->mlx, solong->image[index]);
			index++;
		}
		free(solong->image);
	}
	if (solong->mlx)
		mlx_terminate(solong->mlx);
	exit(stt);
}
