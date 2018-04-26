/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_swap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 14:56:13 by kyork             #+#    #+#             */
/*   Updated: 2016/09/24 15:24:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ary_swap(t_array *ary, size_t i, size_t j)
{
	char	tmp;
	char	*a;
	char	*b;
	size_t	cpyidx;

	if (i > ary->item_count)
		return ;
	if (j > ary->item_count)
		return ;
	if (i == j)
		return ;
	a = ((char*)ary->ptr) + (i * ary->item_size);
	b = ((char*)ary->ptr) + (j * ary->item_size);
	cpyidx = 0;
	while (cpyidx < ary->item_size)
	{
		tmp = a[cpyidx];
		a[cpyidx] = b[cpyidx];
		b[cpyidx] = tmp;
		cpyidx++;
	}
}
