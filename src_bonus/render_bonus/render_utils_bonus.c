/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:21:18 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/07 19:25:01 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

#define MINIMAP_RADIUS 100
#define MINIMAP_SCALE 10

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			put_pixel(img, x + j, y + i, color);
		}
	}
}

void	draw_square_(t_img *img, int x, int y, int size, int color)
{
	for (int i = -size / 2; i < size; i++)
	{
		for (int j =- size / 2; j < size; j++)
		{
			put_pixel(img, x + j, y + i, color);
		}
	}
}

// Filled circle
int draw_filled_circle(t_img *img, int cx, int cy, int r, int color)
{
    for (int y = -r; y <= r; y++)
    {
        for (int x = -r; x <= r; x++)
        {
            if (x * x + y * y <= r * r)
                put_pixel(img, cx + x, cy + y, color);
        }
    }
    return (0);
}

// Circle outline
int draw_circle(t_img *img, int cx, int cy, int r, int color)
{
    for (int angle = 0; angle < 360; angle++)
    {
        double rad = angle * M_PI / 180.0;
        int x = cx + (int)(cos(rad) * r);
        int y = cy + (int)(sin(rad) * r);
        put_pixel(img, x, y, color);
    }
    return (0);
}

// Bresenham line
int draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        put_pixel(img, x0 + 4, y0 + 4, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
    return (0);
}

void	init_fov_in_loop(t_fov *fov, double angle, double r)
{
	fov->intersection = 0;
	fov->dx = cos(angle);
	fov->dy = sin(angle);
	fov->x = (int)(fov->px + fov->dx * r);
	fov->y = (int)(fov->py + fov->dy * r);
	fov->map_x = fov->x / CELL_SIZE;
	fov->map_y = fov->y / CELL_SIZE;
}

int	check_fov_params(t_game *game, t_fov *fov)
{
	t_door	*door;

	if (fov->map_x < 0 || fov->map_x > game->config.map.width - 1
		|| fov->map_y < 0 || fov->map_y > game->config.map.height - 1)
		return (-1);
	if (!ft_strchr("0134", game->config.map.grid[fov->map_y][fov->map_x])
		|| (game->config.map.grid[fov->map_y][fov->map_x] == '0'
		&& game->config.map.grid[fov->map_y][fov->map_x + 1] == '1'
		&& game->config.map.grid[fov->map_y][fov->map_x - 1] == '1'
		&& game->config.map.grid[fov->map_y - 1][fov->map_x] == '1'
		&& game->config.map.grid[fov->map_y + 1][fov->map_x] == '1'
		))
		fov->intersection = 1;
	if (game->config.map.grid[fov->map_y][fov->map_x] == '1'
		|| fov->intersection)
		return (-1);
	if (game->config.map.grid[fov->map_y][fov->map_x] == '4')
	{
		door = find_door(&game->config, fov->map_x, fov->map_y);
		if (door && !door->is_open)
			return (-1);
	}
	return (0);
}

int	draw_mini_map_fov(t_game *game, int center_x, int center_y)
{
    t_fov	*fov;
    double	r;
    double	angle;

    fov = NULL;
    init_fov(game, &fov);
    r = 0;
    angle = fov->start_angle;
    while (angle <= fov->end_angle)
    {
        r = 0;
        while (r <= fov->range)
        {
            init_fov_in_loop(fov, angle, r);
            if (check_fov_params(game, fov))
                break;

            // conversion monde → minimap
            double dx = (fov->x / (double)CELL_SIZE - game->config.player.pos.x) * MINIMAP_SCALE;
            double dy = (fov->y / (double)CELL_SIZE - game->config.player.pos.y) * MINIMAP_SCALE;

            int screen_x = center_x + (int)dx;
            int screen_y = center_y + (int)dy;

            if (dx * dx + dy * dy <= MINIMAP_RADIUS * MINIMAP_RADIUS)
                put_pixel(&game->mlx.screen, screen_x, screen_y, 0xf5b342);

            r += 1.0;
        }
        angle += fov->step;
    }
    return (0);
}

// int	draw_mini_map_fov(t_game *game)
// {
// 	t_fov	*fov;
// 	double	r;
// 	double	angle;

// 	fov = NULL;
// 	init_fov(game, &fov);
// 	r = 0;
// 	angle = fov->start_angle;
// 	while (angle <= fov->end_angle)
// 	{
// 		r = 0;
// 		while (r <= fov->range)
// 		{
// 			init_fov_in_loop(fov, angle, r);
// 			if (check_fov_params(game, fov))
// 				break ;
// 			if (put_pixel(&game->mlx.screen, fov->x, fov->y, 0xf5b342))
// 				return (-1);
// 			r += 1.0;
// 		}
// 		angle += fov->step;
// 	}
// 	return (0);
// }

int	draw_mini_map_check(t_game *game, int map_x, int map_y)
{
	if (game->config.map.grid[map_y][map_x] == '1')
	{
		if (draw_map_wall_cell(&game->mlx.screen,
				map_x, map_y, 0xFF9000))
			return (-1);
	}
	else if (game->config.map.grid[map_y][map_x] == '3')
	{
		if (is_item_active(&game->config, map_x, map_y))
		{
			if (draw_map_item_cell(game, map_x, map_y, 0x00FF00))
				return (-1);
		}
	}
	else if (game->config.map.grid[map_y][map_x] == '4')
	{
		if (draw_map_door_cell(game, map_x, map_y, 0XFF0000))
			return (-1);
	}
	
	return (0);
}

int draw_mini_map(t_game *game, t_img screen)
{
    int center_x = MINIMAP_RADIUS + 20;
    int center_y = HEIGHT - MINIMAP_RADIUS - 20;

    // background circle
    draw_filled_circle(&screen, center_x, center_y, MINIMAP_RADIUS + 10, 0x528697);

    for (int y = 0; y < game->config.map.height; y++)
    {
        for (int x = 0; x < (int)ft_strlen(game->config.map.grid[y]); x++)
        {
            double dx = (x + 0.5 - game->config.player.pos.x) * MINIMAP_SCALE;
            double dy = (y + 0.5 - game->config.player.pos.y) * MINIMAP_SCALE;

            int screen_x = center_x + (int)dx;
            int screen_y = center_y + (int)dy;

            if (dx*dx + dy*dy <= MINIMAP_RADIUS * MINIMAP_RADIUS)
            {
                if (game->config.map.grid[y][x] == '1')
					draw_square(&screen, screen_x, screen_y, 9, 0x000000);
                    // put_pixel(&screen, screen_x, screen_y, 0xAAAAAA); // wall
				else if (game->config.map.grid[y][x] == '3')
					draw_square_(&screen, screen_x, screen_y, 4, 0xFFFF00);
					// put_pixel(&screen, screen_x, screen_y, 0xFF0000); // item
				else if (game->config.map.grid[y][x] == '4')
					draw_square(&screen, screen_x, screen_y, 8, 0xAAAAAA);
                    // put_pixel(&screen, screen_x, screen_y, 0x00FF00); // item	
                // else
				// 	draw_square(&screen, screen_x, screen_y, 8, 0x333333);
                    // put_pixel(&screen, screen_x, screen_y, 0x333333); // floor
            }
        }
    }

    // player
    // draw_circle(&screen, center_x, center_y, 3, 0x000000);
	draw_square(&screen, center_x, center_y, 9, 0x0000FF);

    // facing direction
	// draw_mini_map_fov(game, center_x, center_y);
	int dir_x = (int)(game->config.player.dir.x * 15);
	int dir_y = (int)(game->config.player.dir.y * 15);
	draw_line(&screen, center_x, center_y,
          center_x + dir_x, center_y + dir_y, 0xFF0000);

    return (0);
}

