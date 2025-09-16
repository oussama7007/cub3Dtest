/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:25:20 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/16 19:14:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_middle_rows(t_map map, int i, t_gc *gc)
{
	int		last_char_idx;
	char	*str_trimmed;

	str_trimmed = ft_strtrim(map.grid[i], " \t\n\r", gc);
	last_char_idx = ft_strlen(str_trimmed) - 1;
	if (str_trimmed[0] != '1' || str_trimmed[last_char_idx] != '1')
		return (print_err("Map error: Invalid row!\n"));
	return (0);
}

void	init_vars(int *front, int *back)
{
	*front = 0;
	*back = 0;
}

int	is_last(t_parse_ctx *context)
{
	return (!context->config->last_map.we_path_flag
		|| !context->config->last_map.so_path_flag
		|| !context->config->last_map.f_color_flag
		|| !context->config->last_map.c_color_flag
		|| !context->config->last_map.no_path_flag
		|| !context->config->last_map.ea_path_flag);
}

int	process_line(t_parse_ctx *context)
{
	int	i;

	i = context->state->i;
	if (is_map_config_line(context->lines[i]))
	{
		if (handle_config_line_err(context->config, context->gc,
				context->lines[i], context->state->map_started))
			return (-1);
	}
	else if (is_map_desc_line(context->lines[i]))
	{
		if (is_last(context))
			return (print_err("Error: the map content must be the last!\n"));
		handle_vals_to_check_for_empty_line(&context->state->i,
			&context->state->map_started,
			&context->state->f_map_line,
			&context->state->l_map_line);
		(*context->map_len)++;
	}
	else if (!is_empty_line(context->lines[i]))
		return (print_err("Error: Invalid configuration line!\n"));
	return (0);
}

int	is_hidden(const char *path)
{
	const char	*base;

	base = path + ft_strlen(path);
	while (base > path && *(base - 1) != '/')
		base--;
	return (base[0] == '.');
}
