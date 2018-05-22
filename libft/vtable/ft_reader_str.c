/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:55:16 by kyork             #+#    #+#             */
/*   Updated: 2018/05/22 14:23:27 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reader.h"
#include <stdlib.h>

static ssize_t				ft_strreader_read(void *state,
		char *buf, size_t len)
{
	t_ft_strreader_state	*st;

	st = state;
	if (st->idx + len > st->cap)
		len = st->cap - st->idx;
	ft_memmove(buf, st->buf + st->idx, len);
	st->idx += len;
	return (len);
}

static void					ft_strreader_free(void *state)
{
	t_ft_strreader_state	*st;

	st = state;
	free(st);
}

t_ft_reader					ft_reader_str(const char *str, size_t len)
{
	t_ft_strreader_state	*st;

	st = ft_memalloc(sizeof(t_ft_strreader_state));
	st->buf = str;
	st->idx = 0;
	st->cap = len;
	return (t_ft_reader){&g_ft_strreader_vtable, st};
}

size_t						ft_strreader_count(t_ft_reader obj)
{
	t_ft_strreader_state	*st;

	vtable_typecheck("t_ft_strreader", obj.vtable, &g_ft_strreader_vtable);
	st = obj.state;
	return (st->idx);
}

const t_ft_reader_vtable	g_ft_strreader_vtable = {
	&ft_strreader_read,
	&ft_strreader_free,
};
