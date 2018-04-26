/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 15:09:11 by kyork             #+#    #+#             */
/*   Updated: 2016/10/01 15:35:33 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ary_remove(t_array *ary, size_t idx)
{
	if (ary->item_cap == 0)
		return (FT_ARY_ERR_ISVIEW);
	if (idx >= ary->item_count)
		return (FT_ARY_ERR_BOUNDS);
	ft_memmove(((char*)ary->ptr) + (idx * ary->item_size),
				((char*)ary->ptr) + ((idx + 1) * ary->item_size),
				(ary->item_count - 1 - idx) * ary->item_size);
	ary->item_count -= 1;
	return (FT_ARY_ERR_OKAY);
}
