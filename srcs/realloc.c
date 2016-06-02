#include "../includes/malloc.h"

static void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;
	size_t			i;

	printf("N = %zu\n", n);
	dest = (unsigned char*)s1;
	src = (unsigned char*)s2;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return ((void*)dest);
}

void			*realloc(void *ptr, size_t size)
{
	void		*tmp = NULL;
	t_block		*head = NULL;

	head = (t_block*)(ptr - HEADER_SIZE);
	if (sizeof(*head) != HEADER_SIZE)
		return (NULL);
	if (size)
	{
		tmp = malloc(size);
		if (!tmp)
			return (NULL);
		if (ptr)
			tmp = ft_memcpy(tmp, ptr, head->size);
	}
	if (ptr)
		free(ptr);
	return (tmp);
}