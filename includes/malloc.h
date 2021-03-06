/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:06:17 by arochard          #+#    #+#             */
/*   Updated: 2016/06/10 18:06:21 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <pthread.h>

# define PAGE_SIZE			(getpagesize())

# define TINY_MIN			1
# define TINY_MAX			128
# define TINY_ZONE			((TINY_MAX*128) - ((TINY_MAX*128) % PAGE_SIZE))

# define SMALL_MIN			129
# define SMALL_MAX			4096
# define SMALL_ZONE			((SMALL_MAX*128) - ((SMALL_MAX*128) % PAGE_SIZE))

# define LARGE_MIN			4097

# define PAGE_SIZE_MUL(x)	(x + (PAGE_SIZE - (x % PAGE_SIZE)))

# define TINY(x) 			(((x <= TINY_MAX) && (x > TINY_MIN)) ? (1) : (0))
# define SMALL(x) 			(((x <= SMALL_MAX) && (x > SMALL_MIN)) ? (1) : (0))
# define LARGE(x) 			((x > LARGE_MIN) ? (1) : (0))

# define TINY_INDEX 		0
# define SMALL_INDEX 		1
# define LARGE_INDEX		2

# define FREE				1
# define USED				0

extern void					*g_base_list[];
extern pthread_mutex_t		g_mutex;

typedef struct s_zone		t_zone;

typedef struct				s_block
{
	int						flag;
	size_t					size;
	struct s_block			*next;
	struct s_block			*prev;
	t_zone					*parent;
}							t_block;

# define HEADER_SIZE		(sizeof(t_block))

struct						s_zone
{
	int						type;
	size_t					size_free;
	int						blocks_used;
	t_block					*begin;
	struct s_zone			*next;
	struct s_zone			*prev;
};

# define ZONE_SIZE			(sizeof(t_zone))

void						*ft_bzero(void *s, size_t n);
void						ft_putchar(char c);
void						ft_putstr(char const *s);
void						ft_puthexa(size_t dec);
void						ft_putnbr(int nb);

int							init_heap(int type, size_t size);
void						split_block(t_block *prev, size_t size);
void						*extend_heap(size_t *size, int type);
t_zone						*new_zone(t_zone *prev, int type, size_t size);
void						first_block(t_zone *zone);

void						free(void *ptr);
void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);

void						show_alloc_mem();
size_t						limit_alloc(size_t size);

#endif
