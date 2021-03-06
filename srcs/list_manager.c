/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:35:50 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:35:53 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			first_block(t_zone *zone)
{
	t_block		*new_b;

	new_b = (void *)zone + ZONE_SIZE;
	zone->begin = new_b;
	new_b->prev = NULL;
	new_b->next = NULL;
	new_b->flag = FREE;
	new_b->size = zone->size_free;
	new_b->parent = zone;
}

void			split_block(t_block *prev, size_t size)
{
	t_block		*new_block;

	new_block = (void *)prev + HEADER_SIZE + size;
	new_block->size = prev->size - size - HEADER_SIZE;
	new_block->flag = FREE;
	new_block->next = prev->next;
	new_block->prev = prev;
	new_block->parent = prev->parent;
	prev->size = size;
	prev->next = new_block;
	prev->flag = USED;
	prev->parent->size_free -= (size + HEADER_SIZE);
	prev->parent->blocks_used++;
}

t_zone			*new_zone(t_zone *prev, int type, size_t size)
{
	t_zone		*new_zone;

	if ((new_zone = (t_zone*)extend_heap(&size, type)) == NULL)
		return (NULL);
	new_zone->size_free = size - ZONE_SIZE - HEADER_SIZE;
	new_zone->prev = prev;
	new_zone->next = NULL;
	new_zone->blocks_used = 0;
	new_zone->type = type;
	if (prev != NULL)
		prev->next = new_zone;
	first_block(new_zone);
	return (new_zone);
}
