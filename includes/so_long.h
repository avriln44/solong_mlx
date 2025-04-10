/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-mngu <thi-mngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:30:12 by thi-mngu          #+#    #+#             */
/*   Updated: 2025/04/09 16:37:58 by thi-mngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include <stdint.h>
# include "../library/MLX42/include/MLX42/MLX42.h"

//Resolution 4k
# define PIXEL 64

//windowlength 3840/64
# define WINDOW_LENGTH 60

//windowwidth 2160/64
# define WINDOW_WIDTH 34

# define BUFFER_SIZE 2041

# define IMG_TYPE 5

# define COLLECT "./textures/collect.png"
# define EXIT "./textures/exit.png"
# define PLAYER "./textures/player.png"
# define SPACE "./textures/space.png"
# define WALL "./textures/wall.png"

typedef struct s_point
{
	int row;
	int col;
} t_point; 

typedef struct s_map
{
	char **game_map;
	char *file_name;
	int player;
	int collect;
	int exit;
	int space;
	int width;
	int length;
	t_point	start;
	t_point end;
} t_map;

typedef enum s_object
{
	C,
	E,
	P,
	S,
	W
}	t_object;


typedef struct s_path
{
    int collected;
    int total_collectibles;
    int exit_found;
} t_path;

typedef struct s_solong
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	**image;
	t_point		current;
	t_point		next;
	int32_t		collected;
	int32_t		moves;
}	t_solong;

//error_handlings
void	game_map_error(int32_t status, char *msg, t_map *map);
void	game_error(t_solong *solong, const char *msg);
void	map_error(char *msg, t_map *map);
void	file_error(char *file, int *fd);



void	get_map(int fd, t_map *map);
void	check_path(t_map *map);
void	map_validation(t_map *map);
void	read_map(char *map_file, t_map *map);


//game
void	load_image(t_solong *solong);
void	display_map(t_solong *solong, int32_t row, int32_t col);
void	key_hook(mlx_key_data_t keydata, void *param);

//utils
char	**ft_copy_2d(char **map);
void	count_objects(t_map *map);
void	ft_free_2d(void **arr);
void	exit_solong(t_solong *solong, int32_t stt);
void	ft_printf_fd(int fd, const char *str);

#endif