/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:26:15 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 14:31:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static char **read_map_file_lines(const char *filename, t_gc *gc)
{
    int fd;
    char    **lines;
    char    *line;
    int     i;

    fd = open(filename, O_RDONLY, 0644);
    if (fd == -1)
        return (NULL);
    lines = gc_malloc(gc, sizeof(char *) * 2048);
    line = NULL;
    i = -1;
    while ((line = get_next_line(fd, gc)) && i < 2047)
        lines[++i] = ft_strdup(line, gc);
    lines[++i] = NULL;
    close(fd);
    return (lines);
}

int    add_sprite(t_config *config, double x, double y, int type)
{
    t_sprite    *new_arr;
    int         i;

    new_arr = malloc(sizeof(t_sprite) * (config->sprites_count + 1));
    if (!new_arr)
        return (print_err("new_arr allocation failed\n"));
    i = -1;
    while (++i < config->sprites_count)
        new_arr[i] = config->sprites[i];
    new_arr[config->sprites_count].x = x + 0.5;
    new_arr[config->sprites_count].y = y + 0.5;
    new_arr[config->sprites_count].type = type;
    new_arr[config->sprites_count].active = true;
    new_arr[config->sprites_count].anim_index = 0;
    if (config->sprites)
        free(config->sprites);
    config->sprites = new_arr;
    config->sprites_count++;
    return (0);
}

int    add_door(t_config *config, int x, int y)
{
    t_door  *new_arr;
    int     i;

    new_arr = malloc(sizeof(t_door) * (config->doors_count + 1));
    if (!new_arr)
        return (print_err("new_arr allocation failed\n"));
    i = -1;
    while (++i < config->doors_count)
        new_arr[i] = config->doors[i];
    new_arr[config->doors_count].x = x + 0.5;
    new_arr[config->doors_count].y = y + 0.5;
    new_arr[config->doors_count].anim_timer = 0;
    new_arr[config->doors_count].is_open = false;
    new_arr[config->doors_count].type = DOOR_TYPE;
    new_arr[config->doors_count].door_offset = 0.0;
    new_arr[config->doors_count].state = 0;
    new_arr[config->doors_count].side_hit = 0;
    if (config->doors)
        free(config->doors);
    config->doors = new_arr;
    config->doors_count++;
    return (0);
}

int    fill_sprites_and_doors_arrays(t_config *config)
{
    int i;
    int j;

    i = -1;
    while (config->map.grid[++i])
    {
        j = -1;
        while (config->map.grid[i][++j])
        {
            if (config->map.grid[i][j] == '3')
            {
                if (add_sprite(config, j, i, ITEM_TYPE))
                    return (-1);
            }
            else if (config->map.grid[i][j] == '4')
            {
                if (add_door(config, j, i))
                    return (-1);
            }
        }
    }
    return (0);
}

int	parse_cub3d_map(t_config *config, t_gc *gc, const char *filename)
{
    char    **lines;
    size_t  map_desc_len;

    map_desc_len = 0;
    config->sprites = NULL;
    config->sprites_count = 0;
    config->doors = NULL;
    config->doors_count = 0;
    if (ft_strncmp(filename + (ft_strlen(filename) - 4), ".cub", 4))
        return (print_err("File error: invalid file; need .cub extension file\n"));
    lines = read_map_file_lines(filename, gc);
    if (!lines)
        return (print_err("Map error: Failed when getting map lines!\n"));
    if (parse_elements(config, gc, lines, &map_desc_len)
        || validate_config(config, gc) 
        || validate_map(config, gc, map_desc_len))
        return (-1);
    config->map.grid[(int)config->player.pos.y][(int)config->player.pos.x] = '0';

    if (fill_sprites_and_doors_arrays(config))
        return (-1);
    
    return (0);
}
