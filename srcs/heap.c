/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:35:02 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:35:06 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	int		zone_size(int type)
{
	if (!type)
		return (TINY_ZONE);
	else
		return (SMALL_ZONE);
}

void			*extend_heap(size_t *size, int type)
{
	void		*request;

	if (type != LARGE_INDEX)
		*size = zone_size(type);
	else
		*size += ZONE_SIZE + HEADER_SIZE;
	if (*size % PAGE_SIZE != 0)
		*size = PAGE_SIZE_MUL(*size);
	request = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE
		| MAP_ANON, -1, 0);
	if (request == MAP_FAILED)
		return (NULL);
	return (request);
}

int				init_heap(int type, size_t size)
{
	t_zone		*tmp;

	if ((tmp = (t_zone*)extend_heap(&size, type)) == NULL)
		return (-1);
	tmp->size_free = size - ZONE_SIZE - HEADER_SIZE;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->blocks_used = 0;
	tmp->type = type;
	first_block(tmp);
	g_base_list[type] = tmp;
	return (0);
}
