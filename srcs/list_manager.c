#include "../includes/malloc.h"

static void		first_block(t_zone *zone, size_t size)
{
	t_block		*new_b;

	new_b = (void *)zone + ZONE_SIZE;
	zone->begin = new_b;
	new_b->prev = NULL;
	new_b->next = NULL;
	new_b->flag = FREE;
	new_b->size = size;
	new_b->parent = zone;
}

static size_t		type_alloc_size(int type, size_t size)
{
	if (type == TINY_INDEX)
		return TINY_ZONE;
	else if ( type == SMALL_INDEX)
		return SMALL_ZONE;
	return PAGE_SIZE_MUL(size);
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
	prev->parent->sizeFree -= (size + HEADER_SIZE);
	prev->parent->blocks_used++;
}

t_zone			*new_zone(t_zone *prev, int type, size_t size)
{
	t_zone		*new_zone;
	size_t		bsize;

	bsize = type_alloc_size(type, size);
	if ((new_zone = (t_zone*)extend_heap(bsize)) == NULL)
		return (NULL);
	new_zone->sizeFree = bsize - ZONE_SIZE - HEADER_SIZE;
	new_zone->prev = prev;
	new_zone->next = NULL;
	new_zone->blocks_used = 0;
	new_zone->type = type;
	if (prev != NULL)
		prev->next = new_zone;
	first_block(new_zone, (bsize - ZONE_SIZE - HEADER_SIZE));
	return (new_zone);
}