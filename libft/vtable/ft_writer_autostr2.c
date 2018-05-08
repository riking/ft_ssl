/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_autostr2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:57:46 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:58:59 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_writer.h"

char						*ft_autostrwriter_get(t_ft_writer obj)
{
	t_ft_autostrwriter_state	*st;

	vtable_typecheck("ft_autostrwriter",
			obj.vtable, &g_ft_autostrwriter_vtable);
	st = obj.state;
	return ((char*)ft_ary_get(&st->ary, 0));
}

size_t						ft_autostrwriter_count(t_ft_writer obj)
{
	t_ft_autostrwriter_state	*st;

	vtable_typecheck("ft_autostrwriter",
			obj.vtable, &g_ft_autostrwriter_vtable);
	st = obj.state;
	return (st->ary.item_count);
}
