#include "../includes/malloc.h"

static	int		zone_size(int type)
{
	if (!type)
		return TINY_ZONE;
	else
		return SMALL_ZONE;
}

void	*extend_heap(size_t *size, int type)
{
	void		*request;

	if (type != LARGE_INDEX)
		*size = zone_size(type);
	else
		*size += ZONE_SIZE + HEADER_SIZE;
	//printf("Size HEAP : %zu\n", *size);
	if (*size % PAGE_SIZE != 0)
		*size = PAGE_SIZE_MUL(*size);

	//printf("Request size:%zu\n", *size);
	request = mmap(NULL, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (request == MAP_FAILED)
		return (NULL);
	return (request);
}

int	init_heap(int type, size_t size)
{
	t_zone		*tmp;

	if ((tmp = (t_zone*)extend_heap(&size, type)) == NULL)
		return (-1);
	tmp->sizeFree = size - ZONE_SIZE - HEADER_SIZE;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->blocks_used = 0;
	tmp->type = type;
	first_block(tmp);
	baseList[type] = tmp;
	//printf("Tmp Ptr: %p\n", baseList[type]);
	return (0);
}