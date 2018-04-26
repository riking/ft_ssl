/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:38:36 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:45:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_private.h"

static inline void	*adj_ptr(void *ptr, size_t offset)
{
	char	*mem;

	mem = ptr;
	return (mem + offset);
}

t_ar_block			*arena_getblock(t_arena *a, void *ptr)
{
	size_t		idx;
	t_ar_block	*b;

	b = (t_ar_block*)a->blocks.ptr;
	idx = 0;
	while (idx < a->blocks.item_count)
	{
		if (b[idx].block <= ptr && ptr <= adj_ptr(b[idx].block, b[idx].size))
		{
			return (&b[idx]);
		}
		idx++;
	}
	return (NULL);
}

t_ar_block			*arena_findblock(t_arena *a, size_t free_size)
{
	size_t		idx;
	t_ar_block	*b;

	b = (t_ar_block*)a->blocks.ptr;
	idx = 0;
	while (idx < a->blocks.item_count)
	{
		if (b[idx].size - b[idx].used >= free_size)
			return (&b[idx]);
		idx++;
	}
	return (NULL);
}
