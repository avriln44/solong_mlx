/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr_3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:06:02 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/03/23 13:49:25 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_free_arr_3d(char ***arr)
// {
// 	int	i;

// 	if (!arr)
// 		return ;
// 	i = 0;
// 	while (arr[i])
// 	{
// 		ft_free_arr_2d(arr[i]);
// 		arr[i] = NULL;
// 		i++;
// 	}
// 	free(arr);
// }

#include <stdlib.h>
#include <stdio.h>

void	ft_free_arr_3d(char ***arr)
{
	int i;
	int j;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			// Optional debug print to trace freeing
			// printf("Freeing arr[%d][%d]: %s\n", i, j, arr[i][j]);
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
	// printf("Freed the whole 3D array\n");
}

