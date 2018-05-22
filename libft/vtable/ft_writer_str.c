/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:24:04 by kyork             #+#    #+#             */
/*   Updated: 2018/05/22 14:23:36 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_writer.h"
#include <stdlib.h>

static ssize_t				ft_strwriter_write(void *state,
		const char *buf, size_t len)
{
	t_ft_strwriter_state	*st;

	st = state;
	if (st->idx + len > st->cap)
		len = st->cap - st->idx;
	ft_memmove(st->buf + st->idx, buf, len);
	st->idx += len;
	return (len);
}

static void					ft_strwriter_free(void *state)
{
	t_ft_strwriter_state	*st;

	st = state;
	free(st);
}

t_ft_writer					ft_writer_str(char *str, size_t len)
{
	t_ft_strwriter_state	*st;

	st = ft_memalloc(sizeof(t_ft_strwriter_state));
	st->buf = str;
	st->idx = 0;
	st->cap = len;
	return (t_ft_writer){&g_ft_strwriter_vtable, st};
}

size_t						ft_strwriter_count(t_ft_writer obj)
{
	t_ft_strwriter_state	*st;

	vtable_typecheck("t_ft_strwriter", obj.vtable, &g_ft_strwriter_vtable);
	st = obj.state;
	return (st->idx);
}

const t_ft_writer_vtable	g_ft_strwriter_vtable = {
	&ft_strwriter_write,
	&ft_strwriter_free,
};
