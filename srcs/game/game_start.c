/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:27:36 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/09 16:41:37 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	disable_current_collectible(t_solong *solong)
{
	int32_t	i;

	i = 0;
	while (i < solong->map->collect)
	{
		if (solong->image[C]->instances[i].x == solong->current.col * PIXEL
			&& solong->image[C]->instances[i].y == solong->current.row * PIXEL)
		{
			solong->image[C]->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}
static void	moves_count(t_solong *solong)
{
	write(1, "Moves: ", 7);
	ft_putnbr_fd(solong->moves, 1);
	write(1, "\n", 1);
}

static void	move_player(t_solong *solong)
{
	solong->current = solong->next;
	solong->moves++;
	moves_count(solong);
	if (solong->map->game_map[solong->current.row][solong->current.col] == 'C')
	{
		solong->map->game_map[solong->current.row][solong->current.col] = '0';
		disable_current_collectible(solong);
		solong->collected++;
	}
	else if (solong->map->game_map[solong->current.row][solong->current.col] == 'E' 
			&& solong->collected == solong->map->collect)
	{
		ft_printf_fd(1, "You win!\n");
		exit(EXIT_SUCCESS);
	}
	solong->image[P]->instances[0].x = solong->current.col * PIXEL;
	solong->image[P]->instances[0].y = solong->current.row * PIXEL;
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*solong;

	solong = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(solong->mlx);
			return ;
		}
		solong->next = solong->current;
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		{
			if (solong->current.row > 0)
				solong->next.row--;
		}
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		{
			if (solong->current.row < solong->map->width - 1)
				solong->next.row++;
		}
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		{
			if (solong->current.col > 0)
				solong->next.col--;
		}
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		{
			if (solong->current.col < solong->map->length - 1)
				solong->next.col++;
		}
		else
			return;
		if (solong->map->game_map[solong->next.row][solong->next.col] != '1') 
			move_player(solong);
	}
}

