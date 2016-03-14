#include "../includes/malloc.h"

static	int	type_alloc(size_t size)
{
	if (TINY(size))
		return TINY_INDEX;
	else if (SMALL(size))
		return SMALL_INDEX;
	return LARGE_INDEX;
}

t_block		*find_block(int type, size_t size, size_t total_size)
{
	if (baseList[type] == NULL)
	{
		extand_heap(type, size);
	}
	//TODO
}

void		*malloc(size_t size)
{
	int	type;
	size_t	total_size;
	t_block	*block;

	if (!size)
		return (NULL);
	total_size = size + HEADER_SIZE;
	type = type_alloc(size);
	block = find_block(type, size, total_size);
	if (block == NULL)
		return (NULL);
	return ((void*)block + HEADER_SIZE)
	// TODO
}