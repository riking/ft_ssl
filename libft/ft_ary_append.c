/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 14:37:55 by kyork             #+#    #+#             */
/*   Updated: 2016/10/01 15:34:38 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ary_append(t_array *ary, void *item)
{
	int		status;

	if (ary->item_cap == 0)
		return (FT_ARY_ERR_ISVIEW);
	if (ary->item_count + 1 > ary->item_cap)
	{
		status = ft_ary_grow(ary, ary->item_cap * FT_ARY_GROW_FACTOR);
		if (status != 0)
			return (status);
	}
	ft_memcpy(((char*)ary->ptr) + (ary->item_size * ary->item_count),
			item, ary->item_size);
	ary->item_count += 1;
	return (FT_ARY_ERR_OKAY);
}
