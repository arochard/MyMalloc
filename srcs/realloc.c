/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:36:09 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:36:12 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void				*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;
	size_t				i;

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

static int				realloc_bis(t_block *head, void *ptr,
	size_t size, void *tmp)
{
	if (!head->parent)
		return (-1);
	if (size)
	{
		tmp = malloc(size);
		if (!tmp)
			return (-1);
		if (ptr)
			tmp = ft_memcpy(tmp, ptr, head->size);
	}
	if (ptr)
		free(ptr);
	return (1);
}

void					*realloc(void *ptr, size_t size)
{
	void				*tmp;
	t_block				*head;

	tmp = NULL;
	head = NULL;
	pthread_mutex_lock(&g_mutex);
	head = (t_block*)(ptr - HEADER_SIZE);
	if (realloc_bis(head, ptr, size, tmp) == -1)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex);
	return (tmp);
}
