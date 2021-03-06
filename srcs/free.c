/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:34:27 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:34:33 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		free_zone(t_zone *zone)
{
	size_t		size;

	if (!zone->prev && !zone->next && zone->type != LARGE_INDEX)
		return ;
	if (zone->prev)
		zone->prev->next = zone->next;
	else
		g_base_list[zone->type] = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	if (zone->type == TINY_INDEX)
		size = TINY_ZONE + ZONE_SIZE + HEADER_SIZE;
	else if (zone->type == SMALL_INDEX)
		size = SMALL_ZONE + ZONE_SIZE + HEADER_SIZE;
	else
		size = PAGE_SIZE_MUL(zone->size_free + ZONE_SIZE + HEADER_SIZE);
	ft_bzero((void *)zone, size);
	munmap((void *)zone, size);
}

static void		defrag(t_block *block)
{
	if (block->next)
	{
		if (block->next->flag == FREE)
		{
			block->size += block->next->size + HEADER_SIZE;
			block->next = block->next->next;
			if (block->next->next)
				block->next->next->prev = block;
			ft_bzero((void *)block + HEADER_SIZE, block->size);
		}
	}
	if (block->prev)
	{
		if (block->prev->flag == FREE)
		{
			block->prev->size += block->size + HEADER_SIZE;
			block->prev->next = block->next;
			if (block->next)
				block->next->prev = block->prev;
			ft_bzero((void *)block->prev + HEADER_SIZE, block->prev->size);
		}
	}
}

void			free(void *ptr)
{
	t_block		*block;
	t_zone		*zone;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	block = (t_block *)(ptr - HEADER_SIZE);
	if (!block->parent)
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	block->flag = FREE;
	zone = block->parent;
	zone->blocks_used--;
	zone->size_free += block->size + HEADER_SIZE;
	if (zone->blocks_used <= 0 || zone->type == LARGE_INDEX)
		free_zone(zone);
	else
		defrag(block);
	ptr = NULL;
	pthread_mutex_unlock(&g_mutex);
}
