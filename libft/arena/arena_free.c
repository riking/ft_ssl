/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:06:37 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:43:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_private.h"

static inline void	*adj_ptr(void *ptr, size_t offset)
{
	char	*mem;

	mem = ptr;
	return (mem + offset);
}

static void			block_free(t_arena *a, t_ar_block *b, void *ptr)
{
	size_t		idx;
	t_ar_alloc	*c;

	c = (t_ar_alloc*)b->allocs.ptr;
	idx = 0;
	while (idx < b->allocs.item_count)
	{
		if (c[idx].ptr == ptr)
		{
			if (c[idx].is_free)
				arena_badfree(a, ptr, "already freed");
			else
				c[idx].is_free = 1;
			ASAN_POISON(ptr, c[idx].size);
			return ;
		}
		idx++;
	}
	arena_badfree(a, ptr, "not at start of an allocation");
}

void				ar_free(t_arena *a, void *ptr)
{
	size_t		idx;
	t_ar_block	*b;

	if (a->magic != MAGIC)
		arena_badop(a, "bad magic in arena header");
	b = (t_ar_block*)a->blocks.ptr;
	idx = 0;
	while (idx < a->blocks.item_count)
	{
		if (b[idx].block <= ptr && ptr <= adj_ptr(b[idx].block, b[idx].size))
		{
			block_free(a, &b[idx], ptr);
			return ;
		}
		idx++;
	}
	arena_badfree(a, ptr, "not allocated by this arena");
}
