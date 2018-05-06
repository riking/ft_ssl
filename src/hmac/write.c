/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 14:04:33 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 14:40:33 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmac.h"
#include <stdlib.h>

ssize_t				hmac_write(void *state, t_u8 *buf, size_t len)
{
	t_hmac_state	*st;

	st = state;
	return (st->inner.vtable->write(st->inner.state, buf, len));
}

void				hmac_finish(void *state, t_u8 *outbuf)
{
	t_hmac_state	*st;
	t_u8			*midhash;
	void			*tmp_outer;

	st = state;
	midhash = malloc(st->my_vtable.output_size);
	st->inner.vtable->finish(st->inner.state, midhash);
	tmp_outer = st->outer.vtable->init(st->outer.state);
	st->outer.vtable->write(tmp_outer, st->opad, st->my_vtable.block_size);
	st->outer.vtable->write(tmp_outer, midhash, st->my_vtable.output_size);
	st->outer.vtable->finish(tmp_outer, outbuf);
	st->outer.vtable->free(tmp_outer);
	free(midhash);
	return ;
}
