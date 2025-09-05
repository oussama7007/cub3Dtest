/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:03:39 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 17:07:40 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	check_middle_rows(t_map map, int i)
{
	int	last_char_idx;

	last_char_idx = ft_strlen(map.grid[i]) - 1;
	if ((map.grid[i][0] != '1' && !ft_isspace(map.grid[i][0]))
		|| (map.grid[i][last_char_idx] != '1'
		&& !ft_isspace(map.grid[i][last_char_idx])))
		return (print_err("Map error: invalid walls!\n"));
	return (0);
}

void	init_vars(int *front, int *back)
{
	*front = 0;
	*back = 0;
}

int	find_player_position(t_config *config, char **tmp_map)
{
	int	i;
	int	player_count;

	i = -1;
	player_count = 0;
	while (tmp_map[++i])
	{
		if (check_player_count(tmp_map, &player_count, i))
			return (-1);
		if (player_count == 1 && (ft_strchr(tmp_map[i], 'N')
				|| ft_strchr(tmp_map[i], 'S') || ft_strchr(tmp_map[i], 'E')
				|| ft_strchr(tmp_map[i], 'W')))
			set_player_details(config, tmp_map, i);
	}
	return (0);
}
