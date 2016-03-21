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
	while (ret != NULL && (ret->size < size || ret->flag == USED))
		ret = ret->next;
	if (ret == NULL)
		return (NULL);
	if (ret->size == size)
	{
		ret->flag = USED;
		zone->sizeFree -= size;
		zone->blocks_used++;
	}
	else
		split_block(ret, size);
	return (ret);
}

static t_block			*find_block(int type, size_t size)
{
	t_block		*ret;
	t_zone		*tmp;

	ret = NULL;
	tmp = (t_zone*)baseList[type];
	while (tmp != NULL && ret == NULL)
	{
		ret = find_block_in_zone(tmp, size);
		tmp = tmp->next;
	}
	if (tmp == NULL && ret == NULL)
	{
		if (type == LARGE_INDEX && baseList[type] == NULL)
		{
			tmp = new_zone(NULL, type, size);
			baseList[type] = tmp;
		}
		else
			tmp = new_zone(tmp->prev, type, size);
		ret = find_block_in_zone(tmp, size);
	}
	return (ret);
}

void			*malloc(size_t size)
{
	int		type;
	t_block		*block;

	if (!size)
		return (NULL);
	if (baseList[TINY_INDEX] == NULL && baseList[SMALL_INDEX] == NULL)
	{
		if (init_heap() == -1)
			return (NULL);
	}
	type = type_alloc(size);
	block = find_block(type, size);
	if (block == NULL)
		return (NULL);
	return ((void*)block + HEADER_SIZE);
}