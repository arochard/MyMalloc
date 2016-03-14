#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <sys/mman.h>

#define PAGE_SIZE	(getpagesize())
/***** Size of list type *****/

#define TINY_MIN	1
#define TINY_MAX	128
#define TINY_ZONE	((TINY_MAX*128) - ((TINY_MAX*128) % PAGE_SIZE))

#define SMALL_MIN	129
#define SMALL_MAX	1024
#define SMALL_ZONE	((SMALL_MAX*128) - ((SMALL_MAX*128) % PAGE_SIZE))

#define LARGE_MIN	1025
#define LARGE_ZONE(x)(x + (PAGE_SIZE - (x % PAGE_SIZE)))

/*************************/

/*** Macro test type list ***/

#define TINY(x) (((x <= TINY_MAX) && (x > TINY_MIN)) ? (true) : (false))
#define SMALL(x) (((x <= SMALL_MAX) && (x > SMALL_MIN)) ? (true) : (false))
#define LARGE(x) ((x > LARGE_MIN) ? (true) : (false))



/*************************/

/*** Index of array of list ***/

#define TINY_INDEX 0
#define SMALL_INDEX 1
#define LARGE_INDEX 2

/*************************/

#define FREE		1
#define USED		0

//Array of pointers on the lists (GLOBAL)
void	*baseList[] = {NULL, NULL, NULL};

typedef struct 			s_block
{
	int 			flag;
	size_t			size;
	struct s_block		*next;
	struct s_block		*prev;
}				t_block;

#define HEADER_SIZE	(sizeof(struct s_block))

typedef struct 			s_zone
{
	int			sizeFree;
	t_block			*begin;
	struct s_zone 		*next;
	struct s_zone 		*pev;
}				t_zone;

/******* Prototype *******/

int			init_heap();
void			split_block(t_block *prev, size_t size);

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);

/************************/

#endif