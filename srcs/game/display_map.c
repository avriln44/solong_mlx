/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:44:47 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/09 16:25:51 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void image_to_window(t_solong *solong, mlx_image_t *img, int32_t row, int32_t col)
{
    if (row < 0 || col < 0 || row >= solong->map->width || col >= solong->map->length)
    {
        return ;
    }
    if (mlx_image_to_window(solong->mlx, img, col * PIXEL, row * PIXEL) < 0)
        game_error(solong, mlx_strerror(mlx_errno));
}

void display_map(t_solong *solong, int32_t row, int32_t col)
{
    row = 0;

    while (row < solong->map->width)
    {
        col = 0;
        while (col < solong->map->length)
        {
            if (solong->map->game_map[row][col] == '1')
                image_to_window(solong, solong->image[W], row, col);
            else
            {
                image_to_window(solong, solong->image[S], row, col);
                if (solong->map->game_map[row][col] == 'C')
                    image_to_window(solong, solong->image[C], row, col);
                else if (solong->map->game_map[row][col] == 'E')
                    image_to_window(solong, solong->image[E], row, col);
            }
            col++;
        }
        row++;
    }
    image_to_window(solong, solong->image[P], solong->current.row, solong->current.col);
}

