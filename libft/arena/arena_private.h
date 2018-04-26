/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:09:40 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:45:35 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_PRIVATE_H
# define ARENA_PRIVATE_H

# include "arena.h"

# define MAGIC 0x4152416c6c6f63ULL
# define DEFAULT_SIZE 4096 * 16

# if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#  define ASAN_POISON(addr, size)  __asan_poison_memory_region((addr), (size))
#  define ASAN_UNPOISON(addr, sz)  __asan_unpoison_memory_region((addr), (sz))
# else
#  define ASAN_POISON(addr, size)   ((void)(addr), (void)(size))
#  define ASAN_UNPOISON(addr, size) ((void)(addr), (void)(size))
# endif

/*
** Represents a single allocation inside an arena.
** size:	size of the allocation
** ptr:		pointer to start of block
** next:	next allocation inside arena
** is_free:	true if allocation was freed
*/
typedef struct	s_ar_alloc {
	size_t		size;
	void		*ptr;
	int			is_free;
}				t_ar_alloc;

/*
** Represents a block of underlying memory for the allocation arena.
** block:	pointer to start of block
** size:	size of underlying memory area
** used:	How much of the block has been used
** allocs:	array of t_ar_alloc
*/
typedef struct	s_ar_block {
	void		*block;
	size_t		size;
	size_t		used;
	t_array		allocs;
}				t_ar_block;

void			arena_badop(t_arena *a, char *msg);
void			arena_badfree(t_arena *a, void *ptr, char *msg);

t_ar_block		*arena_getblock(t_arena *a, void *ptr);
t_ar_block		*arena_findblock(t_arena *a, size_t free_size);

#endif
