#include "so_long.h"

void	game_map_error(int32_t status, char *msg, t_map *map)
{
    ft_printf_fd(2, msg);
    if (map->game_map)
        ft_free_2d((void **)map->game_map);
    exit(status);
}

void	game_error(t_solong *solong, const char *msg)
{
	write(1, "Error:\n", 8);
    ft_printf_fd(2, msg);
    exit_solong(solong, EXIT_FAILURE);
}

void	map_error(char *msg, t_map *map)
{
    ft_printf_fd(2, msg);
    if (map->game_map)
        ft_free_2d((void **)map->game_map);
    exit(1);
}

void	file_error(char *file, int *fd)
{
    if (!file)
    {
        ft_printf_fd(2, "Error:\nNo map file provided!\n");
        exit(EXIT_FAILURE);
    }
    if (ft_strncmp(file + ft_strlen(file) - 4, ".ber", 4) != 0)
    {
        ft_printf_fd(2, "Error:\nMap file must have .ber extension!\n");
        exit(EXIT_FAILURE);
    }
    *fd = open(file, O_RDONLY);
    if (*fd == -1)
    {
        ft_printf_fd(2, "Error:\nCould not open map file!\n");
        exit(EXIT_FAILURE);
    }
}