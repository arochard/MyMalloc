#include "../includes/malloc.h"

//Array of pointers on the lists (GLOBAL)
void	*baseList[] = {NULL, NULL, NULL};

//Global variable for thread-safe
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
	t_zone		*tmpPrev;

	ret = NULL;
	if (baseList[type] == NULL)
		init_heap(type, size);
	tmp = (t_zone*)baseList[type];
	while (tmp != NULL && ret == NULL)
	{
		ret = find_block_in_zone(tmp, size);
		tmpPrev = tmp;
		tmp = tmp->next;
	}
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

	pthread_mutex_lock(&mutex);
	if (!size)
	{
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	size = limit_alloc(size);
	type = type_alloc(size);
	block = find_block(type, size);
	if (block == NULL)
	{
		pthread_mutex_unlock(&mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&mutex);
	return ((void*)block + HEADER_SIZE);
}