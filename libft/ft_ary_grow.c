/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_grow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 14:27:54 by kyork             #+#    #+#             */
/*   Updated: 2016/10/11 11:21:03 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** an ary with item_cap == 0 is a view of existing memory and cannot be grown
*/

int			ft_ary_grow(t_array *ary, size_t min_item_cap)
{
	void	*newptr;

	if (ary->item_cap == 0)
		return (FT_ARY_ERR_ISVIEW);
	if (min_item_cap <= ary->item_cap)
		return (FT_ARY_ERR_OKAY);
	newptr = (void*)malloc(ary->item_size * min_item_cap);
	if (!newptr)
		return (FT_ARY_ERR_ALLOC);
	if (ary->ptr)
		ft_memcpy(newptr, ary->ptr, ary->item_size * ary->item_count);
	free(ary->ptr);
	ft_bzero(((char*)newptr) + (ary->item_size * ary->item_count),
			ary->item_size * (min_item_cap - ary->item_count));
	ary->ptr = newptr;
	ary->item_cap = min_item_cap;
	return (0);
}
