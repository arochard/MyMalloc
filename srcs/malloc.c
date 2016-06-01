#include "../includes/malloc.h"

//Array of pointers on the lists (GLOBAL)
void	*baseList[] = {NULL, NULL, NULL};

static	int		type_alloc(size_t size)
{
	if (TINY(size))
		return TINY_INDEX;
	else if (SMALL(size))
		return SMALL_INDEX;
	return LARGE_INDEX;
}

static t_block 		*find_block_in_zone(t_zone *zone, size_t size)
{
	t_block		*ret;

	ret = zone->begin;
	printf("OK1 ret : %p\n", ret);
	while (ret != NULL && (ret->size < size || ret->flag == USED))
		ret = ret->next;
	printf("OK2 ret : %p\n", ret);
	if (ret == NULL)
		return (NULL);
	printf("OK3 size : %zu ret size : %zu\n", size, ret->size);
	if (ret->size == size)
	{
		ret->flag = USED;
		zone->sizeFree -= size;
		zone->blocks_used++;
		printf("OK4\n");
	}
	else
		split_block(ret, size);
	return (ret);
}

static t_block			*find_block(int type, size_t size)
{
	t_block		*ret;
	t_zone		*tmp;
	t_zone		*tmpPrev;

	ret = NULL;
	if (baseList[type] == NULL)
		init_heap(type, size);
	tmp = (t_zone*)baseList[type];
	printf("OK5: tmp:%p\n", baseList[type]);
	while (tmp != NULL && ret == NULL)
	{
		printf("tmp next : %p\n", tmp->next);
		ret = find_block_in_zone(tmp, size);
		tmpPrev = tmp;
		tmp = tmp->next;
	}
	printf("OK6\n");
	if (tmp == NULL && ret == NULL)
	{
		ret = find_block_in_zone(new_zone(tmpPrev, type, size), size);
	}
	return (ret);
}

void			*malloc(size_t size)
{
	int		type;
	t_block		*block;

	if (!size)
		return (NULL);
	type = type_alloc(size);
	block = find_block(type, size);
	if (block == NULL)
		return (NULL);
	printf("%zu %zu %p %zu\n", sizeof(*block->parent), sizeof(block), (void*)block + HEADER_SIZE, block->size);
	return ((void*)block + HEADER_SIZE);
}