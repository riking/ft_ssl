/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 15:09:11 by kyork             #+#    #+#             */
/*   Updated: 2016/10/01 15:38:04 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ary_remove_mul(t_array *ary, size_t idx, size_t count)
{
	if (ary->item_cap == 0)
		return (FT_ARY_ERR_ISVIEW);
	if (idx + count > ary->item_count)
		return (FT_ARY_ERR_BOUNDS);
	ft_memmove(((char*)ary->ptr) + (idx * ary->item_size),
				((char*)ary->ptr) + ((idx + count) * ary->item_size),
				(ary->item_count - count - idx) * ary->item_size);
	ary->item_count -= count;
	return (FT_ARY_ERR_OKAY);
}
