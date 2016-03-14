#include "../includes/malloc.h"

void	split_block(t_block *prev, size_t size)
{
	t_block		*new_block;

	new_block = (void *)prev + HEADER_SIZE + size;
	new_block->size = prev->size - size - HEADER_SIZE;
	new_block->flag = FREE;
	new_block->next = prev->next;
	new_block->prev = prev;
	prev->size = size;
	prev->next = new_block;
}

void	extend_heap(t_zone *prev, int type, size_t size)
{
	t_zone		*new_zone;
	void		*request;
}

int	init_heap()
{


}