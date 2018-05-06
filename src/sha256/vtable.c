/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:48:24 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 15:04:46 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hash.h"
#include "./sha256.h"

#include <stdlib.h>

void					*sha256g_init(void *state)
{
	t_sha256state	*st1;
	t_sha256state	*st2;

	st2 = malloc(sizeof(t_sha256state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	else
	{
		*st2 = sha256_init();
		return (st2);
	}
}

void					sha256g_free(void *state)
{
	t_sha256state	*st;

	st = state;
	free(st);
}

ssize_t					sha256g_write(void *state, t_u8 *buf, size_t len)
{
	t_sha256state	*st;

	st = state;
	sha256_write(st, buf, len);
	return (len);
}

void					sha256g_finish(void *state, t_u8 *outbuf)
{
	t_sha256state	*st;

	st = state;
	sha256_finish(st, outbuf);
}

const t_ft_hash_vtable	g_sha256_hash_vtable = {
	&sha256g_init,
	&sha256g_free,
	&sha256g_write,
	&sha256g_finish,
	SHA256_OUTPUT_SIZE,
	SHA256_BLOCK_SIZE,
};
