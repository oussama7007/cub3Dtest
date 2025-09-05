/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:46:35 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:46:38 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	update_player(t_game *game)
{
	game->move_speed = 0.1;
	game->rot_speed = 0.05;
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		strafe_left(game);
	if (game->keys.d)
		strafe_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	return (0);
}
