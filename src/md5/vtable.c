/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:39:10 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 16:23:37 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hash.h"
#include "./md5.h"

#include <libft.h>
#include <stdlib.h>

void					*md5g_init(void *state)
{
	t_md5state	*st1;
	t_md5state	*st2;

	st2 = ft_memalloc(sizeof(t_md5state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	else
	{
		*st2 = md5_init();
		return (st2);
	}
}

void					md5g_free(void *state)
{
	t_md5state	*st;

	st = state;
	free(st);
}

ssize_t					md5g_write(void *state, t_u8 *buf, size_t len)
{
	t_md5state	*st;

	st = state;
	md5_write(st, buf, len);
	return (len);
}

void					md5g_finish(void *state, t_u8 *outbuf)
{
	t_md5state	*st;

	st = state;
	md5_finish(st, outbuf);
}

const t_ft_hash_vtable	g_md5_hash_vtable = {
	&md5g_init,
	&md5g_free,
	&md5g_write,
	&md5g_finish,
	MD5_OUTPUT_SIZE,
	MD5_BLOCK_SIZE,
};
