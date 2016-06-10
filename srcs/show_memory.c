/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 17:36:25 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 17:36:28 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		print_zone(t_zone *ptr, char *str)
{
	ft_putstr(str);
	ft_putstr(" : ");
	ft_puthexa((size_t)ptr);
	ft_putchar('\n');
	ft_putstr("Size free : ");
	ft_putnbr(ptr->size_free);
	ft_putstr(" bytes\n");
	ft_putstr("Block(s) Used : ");
	ft_putnbr(ptr->blocks_used);
	ft_putchar('\n');
}

static void		show_blocks(t_zone *ptr, char *str)
{
	t_block		*it;

	while (ptr != NULL)
	{
		print_zone(ptr, str);
		it = ptr->begin;
		while (it != NULL)
		{
			if (it->flag == USED)
			{
				ft_puthexa((size_t)it + HEADER_SIZE);
				ft_putstr(" - ");
				ft_puthexa((size_t)it + HEADER_SIZE + it->size);
				ft_putstr(" : ");
				ft_putnbr(it->size);
				ft_putstr(" octets");
				ft_putchar('\n');
			}
			it = it->next;
		}
		ptr = ptr->next;
	}
	ft_putchar('\n');
}

void			show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	if (g_base_list[TINY_INDEX])
		show_blocks((t_zone*)g_base_list[TINY_INDEX], "Tiny");
	if (g_base_list[SMALL_INDEX])
		show_blocks((t_zone*)g_base_list[SMALL_INDEX], "Small");
	if (g_base_list[LARGE_INDEX])
		show_blocks((t_zone*)g_base_list[LARGE_INDEX], "Large");
	pthread_mutex_unlock(&g_mutex);
}
