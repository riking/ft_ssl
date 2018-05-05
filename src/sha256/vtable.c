/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:48:24 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 18:48:50 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hash.h"
#include "./sha256.h"

#include <stdlib.h>

void					*sha256g_init(void)
{
	t_sha256state	st1;
	t_sha256state	*st_p;

	st1 = sha256_init();
	st_p = malloc(sizeof(t_sha256state));
	*st_p = st1;
	return (st_p);
}

void					sha256g_free(void *state)
{
	t_sha256state	*st_p;

	st_p = state;
	free(st_p);
}

ssize_t					sha256g_write(void *state, t_u8 *buf, size_t len)
{
	t_sha256state	*st_p;

	st_p = state;
	sha256_write(st_p, buf, len);
	return (len);
}

void					sha256g_finish(void *state, t_u8 *outbuf)
{
	t_sha256state	*st_p;

	st_p = state;
	sha256_finish(st_p, outbuf);
}

const t_ft_hash_vtable	g_sha256_hash_vtable = {
	&sha256g_init,
	&sha256g_free,
	&sha256g_write,
	SHA256_OUTPUT_SIZE,
	&sha256g_finish,
};

