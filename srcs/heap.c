#include "../includes/malloc.h"

void	*extend_heap(size_t size)
{
	void		*request;

	if ((size % PAGE_SIZE) != 0)
		size = PAGE_SIZE_MUL(size);

	request = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (request == MAP_FAILED)
		return (NULL);
	return (request);
}

int	init_heap()
{
	t_zone		*tiny;
	t_zone		*small;

	if ((tiny = (t_zone*)extend_heap(TINY_ZONE + SMALL_ZONE)) == NULL)
		return (-1);
	small = (void *)tiny + TINY_ZONE;
	tiny->sizeFree = TINY_ZONE - ZONE_SIZE;
	tiny->next = NULL;
	tiny->prev = NULL;
	small->sizeFree = SMALL_ZONE - ZONE_SIZE;
	small->next = NULL;
	small->prev = NULL;
	baseList[TINY_INDEX] = tiny;
	baseList[SMALL_INDEX] = small;
	return (0);
}