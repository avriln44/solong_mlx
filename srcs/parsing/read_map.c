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

static void	count_objects(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->game_map[i])
    {
        j = 0;
        while (map->game_map[i][j])
        {
            if (map->game_map[i][j] == 'P')
                map->player++;
            else if (map->game_map[i][j] == 'E')
                map->exit++;
            else if (map->game_map[i][j] == 'C')
                map->collect++;
            else if (map->game_map[i][j] == '0')
                map->space++;
            else if (map->game_map[i][j] != '1')
                game_map_error(0, "Error:\nInvalid character in map\n", map);
            j++;
        }
        i++;
    }
}

static void allocate_map_memory(t_map *map, int map_size)
{
    map->game_map = (char **)malloc(sizeof(char *) * (map_size + 1));
    if (!map->game_map)
        game_map_error(0, "Error:\nMemory allocation failed\n", map);
}

static void read_map_lines(t_map *map, int fd, int map_size)
{
    char *line;
    int i;

    i = 0;
    while (i < map_size)
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
        // if (ft_strlen(line) == 0)
        // {
        //     free(line);
        //     ft_free_2d((void **)map->game_map);
        //     map_file_error(0, "Error:\nEmpty line in map\n", fd);
        // }
        map->game_map[i] = ft_strdup(line);
        free(line);
        i++;
    }
    // line = get_next_line(fd);
    // if (line)
    // {
    //     free(line);
    //     ft_free_2d((void **)map->game_map);
    //     map_file_error(0, "Error:\nExtra content after map data\n", fd);
    // }
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
        return 0;
    while (read(fd, &current_char, 1) > 0)
    {
        last_char = current_char;
    }
    if (last_char == '\n')
        has_newline = 1;
    close(fd);
    return (has_newline);
}

void get_map(int fd, t_map *map)
{
    int map_size;

    if (has_newline(map->file_name))
        game_map_error(0, "Error:\nTrailing newline at end of map\n", map);
    map_size = count_map_lines(map->file_name);
    if (map_size == 0)
        game_map_error(0, "Error:\nEmpty map\n", map);
    if (map_size == -1)
        game_map_error(0, "Error:\nEmpty line between map data\n", map);
    allocate_map_memory(map, map_size);
    fd = open(map->file_name, O_RDONLY);
    if (fd == -1)
        game_map_error(0, "Error:\nCould not reopen map file\n", map);
    read_map_lines(map, fd, map_size);
	validate_map_shape(map->game_map);
    close(fd);
    count_objects(map);
}

void read_map(char *map_file, t_map *map)
{
    int32_t fd;

    map->file_name = map_file;
    file_validation(map_file, &fd);
    get_map(fd, map);
    map_validation(map);
}