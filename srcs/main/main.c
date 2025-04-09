/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:33:25 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/09 16:38:15 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_solong	solong;

	if (argc != 2)
		file_error("Error: Invalid number of arguments", NULL);

	solong.map = malloc(sizeof(t_map));
	if (!solong.map)
		return (EXIT_FAILURE);
	ft_bzero(solong.map, sizeof(t_map));

	read_map(argv[1], solong.map);

	solong.mlx = mlx_init(solong.map->length * PIXEL, solong.map->width * PIXEL, "so_long", true);
	if (!solong.mlx)
		return (EXIT_FAILURE);

	load_image(&solong);
	display_map(&solong, 0, 0);
	mlx_key_hook(solong.mlx, key_hook, &solong);
	mlx_loop(solong.mlx);
	mlx_terminate(solong.mlx);
	free(solong.map);
	return (EXIT_SUCCESS);
}
