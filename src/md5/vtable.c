/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:39:10 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 18:47:07 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hash.h"
#include "./md5.h"

#include <stdlib.h>

void					*md5g_init(void)
{
	t_md5state	st1;
	t_md5state	*st_p;

	st1 = md5_init();
	st_p = malloc(sizeof(t_md5state));
	*st_p = st1;
	return (st_p);
}

void					md5g_free(void *state)
{
	t_md5state	*st_p;

	st_p = state;
	free(st_p);
}

ssize_t					md5g_write(void *state, t_u8 *buf, size_t len)
{
	t_md5state	*st_p;

	st_p = state;
	md5_write(st_p, buf, len);
	return (len);
}

void					md5g_finish(void *state, t_u8 *outbuf)
{
	t_md5state	*st_p;

	st_p = state;
	md5_finish(st_p, outbuf);
}

const t_ft_hash_vtable	g_md5_hash_vtable = {
	&md5g_init,
	&md5g_free,
	&md5g_write,
	MD5_OUTPUT_SIZE,
	&md5g_finish,
};

