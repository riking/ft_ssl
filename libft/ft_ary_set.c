/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 15:07:25 by kyork             #+#    #+#             */
/*   Updated: 2016/10/27 16:13:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ary_set(t_array *ary, void *item, size_t idx)
{
	if (idx == ary->item_count)
		return (ft_ary_append(ary, item));
	else
	{
		ft_memmove(ft_ary_get(ary, idx), item, ary->item_size);
		return (0);
	}
}
