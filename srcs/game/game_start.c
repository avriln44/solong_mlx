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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:03:44 by hitran            #+#    #+#             */
/*   Updated: 2024/08/28 09:28:06 by hitran           ###   ########.fr       */
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

static void	move_player(t_solong *solong)
{
	solong->current = solong->next;
	write(1, "Total moves: ", 13);
	if (solong->map->game_map[solong->current.row][solong->current.col] == 'C')
	{
		solong->map->game_map[solong->current.row][solong->current.col] = '0';
		disable_current_collectible(solong);
		solong->taken++;
		if (solong->taken == solong->map->collect)
			solong->image[E]->instances[0].enabled = false;
	}
	else if (solong->map->game_map[solong->current.row][solong->current.col] == 'E'
		&& solong->taken == solong->map->collect)
	{
		ft_printf_fd(1, "You win!\n");
		exit(EXIT_SUCCESS);
	}
	solong->image[P]->instances[0].x = solong->current.col * PIXEL;
	solong->image[P]->instances[0].y = solong->current.row * PIXEL;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_solong	*solong;

	solong = (t_solong *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			exit(EXIT_SUCCESS);
		else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			solong->next = (t_point){solong->current.row - 1, solong->current.col};
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			solong->next = (t_point){solong->current.row + 1, solong->current.col};
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			solong->next = (t_point){solong->current.row, solong->current.col - 1};
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			solong->next = (t_point){solong->current.row, solong->current.col + 1};
		else
			return ;
		if (solong->map->game_map[solong->next.row][solong->next.col] != '1')
			move_player(solong);
	}
}