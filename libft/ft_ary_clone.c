/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 21:13:59 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 21:18:08 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_array		ft_ary_clone(t_array ary, size_t min_size)
{
	void	*ptr;

	if (ary.item_count > min_size)
		min_size = ary.item_count;
	ptr = ft_memalloc(ary.item_size * min_size);
	if (!ptr)
		return (FT_ARY_NULL);
	ft_memcpy(ptr, ary.ptr, ary.item_size * ary.item_count);
	return ((t_array){ptr, ary.item_size, ary.item_count, min_size});
}
