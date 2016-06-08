#include "../includes/malloc.h"

size_t		limit_alloc(size_t size)
{
	struct	rlimit rl;

	if (getrlimit(RLIMIT_AS, &rl) == -1)
		return (-1);
	return (size);
}