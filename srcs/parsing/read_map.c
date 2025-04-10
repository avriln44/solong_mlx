#include "so_long.h"

static void	validate_map_shape(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        if (ft_strlen(map[0]) != ft_strlen(map[i]))
        {
            ft_printf_fd(2, "Error:\nMap is not rectangular shape.\n");
            ft_free_2d((void **)map);
            exit(0);
        }
        i++;
    }
}

static int	count_map_lines(char *filename)
{
    char *line;
    int count;
    int fd;
    int found_empty = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    count = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (ft_strlen(line) == 1 && line[0] == '\n')
        {
            if (count > 0)
                found_empty = 1;
            free(line);
            continue ;
        }
        if (found_empty)
        {
            free(line);
            close(fd);
            return (-1);
        }
        count++;
        free(line);
    }
    close(fd);
    if (found_empty)
        return (-1);
    return (count);
}

static void allocate_map_memory(t_map *map, int map_lines)
{
    map->game_map = (char **)malloc(sizeof(char *) * (map_lines + 1));
    if (!map->game_map)
        game_map_error(0, "Error:\nMemory allocation failed\n", map);
}

static void read_map_lines(t_map *map, int fd, int map_lines)
{
    char *line;
    int i;

    i = 0;
    while (i < map_lines)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        if (ft_strlen(line) == 1 && line[0] == '\n')
        {
            free(line);
            continue ;
        }
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        map->game_map[i] = ft_strdup(line);
        free(line);
        i++;
    }
    map->game_map[i] = NULL;
    map->width = i;
    map->length = ft_strlen(map->game_map[0]);
}

static int	has_newline(char *filename)
{
    int	fd;
    int	last_char;
    int	current_char;
    int	has_newline;

	last_char = 0;
	has_newline = 0;
	current_char = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    while (read(fd, &current_char, 1) > 0)
        last_char = current_char;
    if (last_char == '\n')
        has_newline = 1;
    close(fd);
    return (has_newline);
}

void get_map(int fd, t_map *map)
{
    int map_lines;

    if (has_newline(map->file_name))
        game_map_error(0, "Error:\nNewline at end of map!\n", map);
    map_lines = count_map_lines(map->file_name);
    if (map_lines == 0)
        game_map_error(0, "Error:\nEmpty map\n", map);
    if (map_lines == -1)
        game_map_error(0, "Error:\nEmpty line between map data\n", map);
    allocate_map_memory(map, map_lines);
    fd = open(map->file_name, O_RDONLY);
    if (fd == -1)
        game_map_error(0, "Error:\nCould not reopen map file\n", map);
    read_map_lines(map, fd, map_lines);
	validate_map_shape(map->game_map);
    close(fd);
    count_objects(map);
}

void read_map(char *map_file, t_map *map)
{
    int32_t fd;

    map->file_name = map_file;
    file_error(map_file, &fd);
    get_map(fd, map);
    map_validation(map);
}