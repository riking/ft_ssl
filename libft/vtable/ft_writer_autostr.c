/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_autostr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:40:30 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:55:46 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_writer.h"
#include <errno.h>
#include <stdlib.h>

static ssize_t				ft_autostrwriter_write(void *state,
		const char *buf, size_t len)
{
	t_ft_autostrwriter_state	*st;

	st = state;
	if (ft_ary_grow(&st->ary, st->ary.item_count + len) < 0)
	{
		errno = ENOMEM;
		return (-1);
	}
	ft_memmove(ft_ary_get(&st->ary, st->ary.item_count), buf, len);
	*(st->dst) = ft_ary_get(&st->ary, 0);
	return (len);
}

static void					ft_autostrwriter_free(void *state)
{
	t_ft_autostrwriter_state	*st;

	st = state;
	if (!st)
		return ;
	if (st->dst)
		*(st->dst) = 0;
	ft_ary_destroy(&st->ary);
	free(st);
}

void						ft_autostrwriter_release(t_ft_writer obj)
{
	t_ft_autostrwriter_state	*st;

	vtable_typecheck("ft_autostrwriter",
			obj.vtable, &g_ft_autostrwriter_vtable);
	st = obj.state;
	st->dst = NULL;
	st->ary.ptr = NULL;
}

t_ft_writer					ft_autostrwriter(char **str)
{
	t_ft_autostrwriter_state	*st;

	st = ft_memalloc(sizeof(t_ft_autostrwriter_state));
	st->ary = ft_ary_create(sizeof(char));
	st->dst = str;
	return (t_ft_writer){&g_ft_autostrwriter_vtable, st};
}

const t_ft_writer_vtable	g_ft_autostrwriter_vtable = {
	&ft_autostrwriter_write,
	&ft_autostrwriter_free,
};
