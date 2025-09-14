/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:22:09 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/13 22:41:12 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	gc_free_all(t_gc *gc)
{
	t_gc_node	*tmp;

	if (!gc)
		return ;
	while (gc->head)
	{
		tmp = gc->head->next;
		free(gc->head->ptr);
		free(gc->head);
		gc->head = tmp;
	}
	free(gc);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void		*ptr;
	t_gc_node	*gc_node;

	if (!gc || size == 0)
	{
		print_err("Error: invalid GC or size\n");
		exit(EXIT_FAILURE);
	}
	ptr = malloc(size);
	if (!ptr)
	{
		gc_free_all(gc);
		print_err("Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	gc_node = malloc(sizeof(t_gc_node));
	if (!gc_node)
	{
		free(ptr);
		gc_free_all(gc);
		print_err("Error: GC node allocation failed\n");
		exit(EXIT_FAILURE);
	}
	gc_node->ptr = ptr;
	gc_node->next = gc->head;
	gc->head = gc_node;
	return (ptr);
}

void	gc_free(t_game *game)
{
	if (!game || !game->gc)
		return ;
	gc_free_all(game->gc);
	free(game);
}