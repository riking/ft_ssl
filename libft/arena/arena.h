/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:44:53 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:24:20 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <sys/types.h>
# include <libft.h>

/*
** Represents an allocation arena.
**
** blocks:	Array of t_ar_block
*/
typedef struct	s_arena {
	size_t		magic;
	t_array		blocks;
}				t_arena;

/*
** Initializes a new arena allocator.
*/
t_arena			*arena_new(void);

/*
** Allocate memory from the arena.
** @param a		arena to allocate from
** @param size	size of the allocation
*/
void			*ar_malloc(t_arena *a, size_t size);

/*
** Allocate zero-initialized memory from the arena.
** @param a		arena to allocate from
** @param size	size of the allocation
*/
void			*ar_zalloc(t_arena *a, size_t size);

/*
** Allocate zero-initialized array of memory from the arena.
** @param a		arena to allocate from
** @param per	size of each item
** @param items	number of items
*/
void			*ar_calloc(t_arena *a, size_t per, size_t items);

/*
** Release memory to the arena.
** If the memory was not allocated from this arena, the program is stopped.
** @param a		arena to allocate from
** @param ptr	pointer to free
*/
void			ar_free(t_arena *a, void *ptr);

/*
** arena_destroy frees all items allocated from the allocation arena.
*/
void			arena_destroy(t_arena *a);

/*
** Set a breakpoint at arena_error_break() for debugging
*/
void			arena_error_break(void);

#endif
