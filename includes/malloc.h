#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

/*************TEMP*************/
#include <stdio.h>
/*************FIN TEMP *********/

#define PAGE_SIZE	(getpagesize())
/***** Size of list type *****/

#define TINY_MIN	1
#define TINY_MAX	128
#define TINY_ZONE	((TINY_MAX*128) - ((TINY_MAX*128) % PAGE_SIZE))

#define SMALL_MIN	129
#define SMALL_MAX	4096
#define SMALL_ZONE	((SMALL_MAX*128) - ((SMALL_MAX*128) % PAGE_SIZE))

#define LARGE_MIN	4097

#define PAGE_SIZE_MUL(x)(x + (PAGE_SIZE - (x % PAGE_SIZE)))

/*************************/

/*** Macro test type list ***/

#define TINY(x) (((x <= TINY_MAX) && (x > TINY_MIN)) ? (1) : (0))
#define SMALL(x) (((x <= SMALL_MAX) && (x > SMALL_MIN)) ? (1) : (0))
#define LARGE(x) ((x > LARGE_MIN) ? (1) : (0))



/*************************/

/*** Index of array of list ***/

#define TINY_INDEX 0
#define SMALL_INDEX 1
#define LARGE_INDEX 2

/*************************/

#define FREE		1
#define USED		0

//Array of pointers on the lists (GLOBAL)
extern void			*baseList[];

typedef struct s_zone 		t_zone;

typedef struct 			s_block
{
	int 			flag;
	size_t			size;
	struct s_block		*next;
	struct s_block		*prev;
	t_zone 			*parent;
}				t_block;

#define HEADER_SIZE	(sizeof(t_block))

struct 				s_zone
{
	size_t			sizeFree;
	int			blocks_used;
	t_block			*begin;
	struct s_zone 		*next;
	struct s_zone 		*prev;
};

#define ZONE_SIZE	(sizeof(t_zone))

/******* Prototype *******/

void			*ft_bzero(void *s, size_t n);

int			init_heap(int type, size_t size);
void			split_block(t_block *prev, size_t size);
void			*extend_heap(size_t *size, int type);
t_zone			*new_zone(t_zone *prev, int type, size_t size);
void			first_block(t_zone *zone, size_t size);

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

/************************/

#endif