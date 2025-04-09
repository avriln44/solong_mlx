#include "so_long.h"

void	map_file_error(int32_t status, char *msg, int fd)
{
    ft_printf_fd(2, msg);
    close(fd);
    exit(status);
}

void	game_map_error(int32_t status, char *msg, t_map *map)
{
    ft_printf_fd(2, msg);
    if (map->game_map)
        ft_free_2d((void **)map->game_map);
    exit(status);
}

void	game_error(const char *msg)
{
	ft_printf_fd(2, msg);
    exit(0);
}

void	map_error(char *msg, t_map *map)
{
    ft_printf_fd(2, msg);
    if (map->game_map)
        ft_free_2d((void **)map->game_map);
    exit(1);
}

void	file_error(char *msg, char *file)
{
    ft_printf_fd(2, msg);
    if (file)
        ft_printf_fd(2, file);
    ft_printf_fd(2, "\n");
    exit(1);
}
void	file_validation(char *file, int *fd)
{
    if (!file)
        file_error("Error: No map file provided!\n", NULL);
    if (ft_strncmp(file + ft_strlen(file) - 4, ".ber", 4) != 0)
        file_error("Error: Map file must have .ber extension!", file);
    *fd = open(file, O_RDONLY);
    if (*fd == -1)
        file_error("Error: Could not open map file!", file);
}