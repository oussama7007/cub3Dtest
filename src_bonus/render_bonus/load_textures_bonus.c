/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:18 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/13 23:13:13 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	destroy_all_images(t_game *game)
{
	int	i;
	int	j;

	/* Walls */
	int z = -1;
	while (++z < 4)
	{
		if (game->textures[z].img_ptr)
		{
			mlx_destroy_image(game->mlx.mlx_ptr, game->textures[z].img_ptr);
			game->textures[z].img_ptr = NULL;
		}
	}

	/* Doors */
	int k = -1;
	while  ( ++k < 2)
	{
		if (game->door_textures[k].img_ptr)
		{
			mlx_destroy_image(game->mlx.mlx_ptr, game->door_textures[k].img_ptr);
			game->door_textures[k].img_ptr = NULL;
		}
	}

	/* Sprites */
	i = -1;
	while ( i++ < SPRITE_TYPE_COUNT)
	{
		j = -1;
		while (++j < game->sprites_frames_count[i])
		{
			if (game->sprite_textures[i][j].img_ptr)
			{
				mlx_destroy_image(game->mlx.mlx_ptr,
					game->sprite_textures[i][j].img_ptr);
				game->sprite_textures[i][j].img_ptr = NULL;
			}
		}
	}

	/* Screen */
	if (game->mlx.screen.img_ptr)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.screen.img_ptr);
		game->mlx.screen.img_ptr = NULL;
	}
}

void	clean_exit_and_exit(t_game *game, int status)
{
	if (game)
	{
		destroy_all_images(game);

		if (game->mlx.win_ptr)
		{
			mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
			game->mlx.win_ptr = NULL;
		}

		if (game->gc)
			gc_free_all(game->gc);
	}
	exit(status);
}

static t_img	load_texture(t_game *game, char *file)
{
	t_img	tex;

	tex.img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			file, &tex.width, &tex.height);
	if (!tex.img_ptr)
	{
		clean_exit_and_exit(game, -1);
	}
	tex.img_data_addr = mlx_get_data_addr(tex.img_ptr, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	if (!tex.img_data_addr)
	{
		clean_exit_and_exit(game, -1);
	}
	return (tex);
}

void	load_wall_all_tex(t_game *game)
{
	game->textures[NORTH] = load_texture(game, game->config.no);
	game->textures[SOUTH] = load_texture(game, game->config.so);
	game->textures[WEST] = load_texture(game, game->config.we);
	game->textures[EAST] = load_texture(game, game->config.ea);
}

void	load_door_all_text(t_game *game)
{
	game->door_textures[0] = load_texture(game, "sprites/door.xpm");
	game->door_textures[1] = load_texture(game, "sprites/door.xpm");
}

static void	load_item_sprites(t_game *game, int type,
	char *files_paths[], int frames_count)
{
	int	i;

	i = -1;
	while (++i < frames_count)
	{
		if (my_access(files_paths[i]))
		{
			print_err("Error occured while opening the file\n");
			clean_exit_and_exit(game, -1);
			exit(-1);
		}
		game->sprite_textures[type][i].img_ptr
			= mlx_xpm_file_to_image(game->mlx.mlx_ptr,
				files_paths[i], &game->sprite_textures[type][i].width,
				&game->sprite_textures[type][i].height);
		game->sprite_textures[type][i].img_data_addr
			= mlx_get_data_addr(game->sprite_textures[type][i].img_ptr,
				&game->sprite_textures[type][i].bits_per_pixel,
				&game->sprite_textures[type][i].line_length,
				&game->sprite_textures[type][i].endian);
	}
	game->sprites_frames_count[type] = frames_count;
}

void	load_all_sprites_tex(t_game *game)
{
	char	*item_sprites[ITEM_FRAMES];

	item_sprites[0] = "sprites/1.xpm";
	item_sprites[1] = "sprites/2.xpm";
	item_sprites[2] = "sprites/3.xpm";
	item_sprites[3] = "sprites/4.xpm";
	item_sprites[4] = "sprites/5.xpm";
	item_sprites[5] = "sprites/6.xpm";
	item_sprites[6] = "sprites/7.xpm";
	item_sprites[7] = "sprites/8.xpm";
	item_sprites[8] = "sprites/9.xpm";
	item_sprites[9] = "sprites/10.xpm";
	item_sprites[10] = "sprites/11.xpm";
	item_sprites[11] = "sprites/12.xpm";
	load_item_sprites(game, ITEM_TYPE, item_sprites, ITEM_FRAMES);
}
