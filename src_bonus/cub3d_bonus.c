/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:24:15 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/08 13:03:50 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int ac, const char **av)
{
	t_game	*game;

	if (ac != 2)
		return (print_err("Usage: ./cub3D <map>.cub\n"));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_err("game allocation failed\n"));
	game->gc = malloc(sizeof(t_gc));
	if (!game->gc)
		return (print_err("Allocation of gc failed\n"));
	game->gc->head = NULL;
	if (parse_cub3d_map(&game->config, game->gc, av[1]))
	{
		gc_free(game);
		return (-1);
	}
	if (rendering(game))
	{
		gc_free(game);
		return (-1);
	}
	gc_free(game);
	return (0);
}
