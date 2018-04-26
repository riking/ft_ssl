/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/24 14:27:31 by kyork             #+#    #+#             */
/*   Updated: 2016/10/27 18:41:11 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SWAP(a, b) tmp = a; a = b; b = tmp;

static size_t	pick_pivot(t_array *ary, size_t len,
		int (*cmp)(void*, void*, size_t, void*), void *cmp_data)
{
	size_t i;
	size_t j;
	size_t k;
	size_t tmp;

	i = 0;
	j = len / 2;
	k = len - 1;
	if (cmp(ft_ary_get(ary, k), ft_ary_get(ary, i),
				ary->item_size, cmp_data) < 0)
	{
		SWAP(k, i);
	}
	if (cmp(ft_ary_get(ary, j), ft_ary_get(ary, i),
				ary->item_size, cmp_data) < 0)
	{
		SWAP(j, i);
	}
	if (cmp(ft_ary_get(ary, k), ft_ary_get(ary, j),
				ary->item_size, cmp_data) < 0)
	{
		SWAP(j, k);
	}
	return (j);
}

static void		sort(t_array *ary, size_t len,
		int (*cmp)(void*, void*, size_t, void*), void *cmp_data)
{
	size_t	lo_storage;
	size_t	idx;

	if (len <= 1)
		return ;
	ft_ary_swap(ary, 0, pick_pivot(ary, len, cmp, cmp_data));
	idx = 0 + 1;
	lo_storage = 0;
	while (idx < 0 + len)
	{
		if (cmp(ft_ary_get(ary, idx), ft_ary_get(ary, 0),
					ary->item_size, cmp_data) <= 0)
		{
			ft_ary_swap(ary, idx, ++lo_storage);
		}
		idx++;
	}
	ft_ary_swap(ary, 0, lo_storage);
	sort(ary, lo_storage - 0, cmp, cmp_data);
	*(char**)&ary->ptr += ary->item_size * (lo_storage + 1);
	sort(ary, len - (lo_storage - 0) - 1, cmp, cmp_data);
	*(char**)&ary->ptr -= ary->item_size * (lo_storage + 1);
}

void			ft_ary_sort(t_array *ary, int (*cmp)(void*, void*,
			size_t, void*), void *cmp_data)
{
	sort(ary, ary->item_count, cmp, cmp_data);
}
