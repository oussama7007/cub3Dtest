/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:25:20 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/11 12:24:23 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

int 	process_line(t_parse_ctx *context)
{
	int i;
	
	i = context->state->i;
	if (is_map_config_line(context->lines[i]))
	{
		if (handle_config_line_err(context->config, context->gc,
				context->lines[i], context->state->map_started))
			return (-1);
	}
	else if (is_map_desc_line(context->lines[i]))
	{
		if (!context->config->last_map.path_flag || !context->config->last_map.color_flag)
			return (print_err("Error: the map content must be the last!\n"));
		handle_vals_to_check_for_empty_line(&context->state->i, &context->state->map_started,
			&context->state->f_map_line, &context->state->l_map_line);
		(*context->map_len)++;
	}
	else if (!is_empty_line(context->lines[i]))
		return (print_err("Error: Invalid configuration line!\n"));
	return 0;
}
