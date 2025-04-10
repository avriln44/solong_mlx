/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:11:35 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/09 15:47:02 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	mlx_image_t	*convert_png(t_solong *solong, char *texture_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(texture_path);
	if (!texture)
		game_error(solong, mlx_strerror(mlx_errno));
	image = mlx_texture_to_image(solong->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		game_error(solong, mlx_strerror(mlx_errno));
	if (!mlx_resize_image(image, PIXEL, PIXEL))
		game_error(solong, mlx_strerror(mlx_errno));
	return (image);
}

void	load_image(t_solong *solong)
{
	solong->image = ft_calloc(IMG_TYPE + 1, sizeof(mlx_image_t));
	if (!solong->image)
		game_error(solong, "Memory allocation failed!");
	solong->image[C] = convert_png(solong, COLLECT);
	solong->image[E] = convert_png(solong, EXIT);
	solong->image[S] = convert_png(solong, SPACE);
	solong->image[W] = convert_png(solong, WALL);
	solong->image[P] = convert_png(solong, PLAYER);
}
