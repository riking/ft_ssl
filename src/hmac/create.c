/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 13:34:38 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 14:56:39 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hmac.h"

#include <libft.h>
#include <ft_printf.h>
#include <stdlib.h>

/*
** if key is too big, hash it.
** if key is small, zero-pad a copy so we can unconditionally free() later
*/
static t_u8*		preprocess_key(t_hmac_state *st,
							const char *key, size_t key_len)
{
	void			*tmp_outer;
	t_u8			*key_hashed;

	key_hashed = malloc(st->my_vtable.output_size);
	ft_bzero(key_hashed, st->my_vtable.output_size);
	if (key_len > st->my_vtable.block_size)
	{
		tmp_outer = st->outer.vtable->init(st->outer.state);
		st->outer.vtable->write(tmp_outer, (t_u8*)key, key_len);
		st->outer.vtable->finish(tmp_outer, key_hashed);
		st->outer.vtable->free(tmp_outer);
		return (key_hashed);
	}
	else if (key_len < st->my_vtable.output_size)
	{
		ft_memcpy(key_hashed, key, key_len);
		return (key_hashed);
	}
	else
	{
		ft_snprintf(NULL, 0, "this codepath is probably a specification bug");
		ft_memcpy(key_hashed, key, st->my_vtable.output_size);
		return (key_hashed);
	}
}

/*
** initalize the pads
*/
static void			init_key(t_hmac_state *st,
							const char *key, size_t key_len)
{
	t_u8			*key_hashed;
	size_t			i;

	ft_bzero(st->ipad, st->my_vtable.block_size);
	ft_bzero(st->opad, st->my_vtable.block_size);
	key_hashed = preprocess_key(st, key, key_len);
	i = 0;
	while (i < st->my_vtable.block_size)
	{
		if (i < st->my_vtable.output_size)
			st->ipad[i] = key_hashed[i] ^ 0x36;
		else
			st->ipad[i] = 0x36;
		if (i < st->my_vtable.output_size)
			st->opad[i] = key_hashed[i] ^ 0x5C;
		else
			st->opad[i] = 0x5C;
		i++;
	}
	ft_bzero(*(t_u8 *volatile *)(&key_hashed), st->my_vtable.output_size);
	free(key_hashed);
}

t_ft_hash			hmac_create(t_ft_hash base,
							const char *key, size_t key_len)
{
	t_ft_hash		ret_hash;
	t_hmac_state	*st;

	st = malloc(sizeof(t_hmac_state));
	*st = (t_hmac_state){{hmacg_clone, hmac_free, hmac_write, hmac_finish,
		base.vtable->output_size, base.vtable->block_size}, {base.vtable, NULL},
		{base.vtable, NULL}, NULL, NULL};
	st->inner.state = base.vtable->init(base.state);
	st->outer.state = NULL;
	st->ipad = malloc(st->my_vtable.block_size);
	st->opad = malloc(st->my_vtable.block_size);
	init_key(st, key, key_len);
	st->inner.vtable->write(st->inner.state, st->ipad,
			st->my_vtable.block_size);
	ret_hash.vtable = &st->my_vtable;
	ret_hash.state = st;
	return (ret_hash);
}

void				hmac_free(void *state)
{
	t_hmac_state	*st;

	st = state;
	if (!st)
		return ;
	free(st->ipad);
	free(st->opad);
	st->inner.vtable->free(st->inner.state);
	st->inner.state = NULL;
	st->outer.vtable->free(st->outer.state);
	st->outer.state = NULL;
	free(st);
}

void				*hmacg_clone(void *state)
{
	t_hmac_state	*st1;
	t_hmac_state	*st2;

	if (!state)
	{
		ft_dprintf(2, "fatal error: attempt to construct a blank HMAC\n");
		abort();
	}
	st1 = state;
	st2 = malloc(sizeof(t_hmac_state));
	st2->my_vtable = st1->my_vtable;
	st2->inner.vtable = st1->inner.vtable;
	st2->inner.state = st1->inner.vtable->init(st1->inner.state);
	st2->outer.vtable = st1->outer.vtable;
	st2->outer.state = st1->outer.vtable->init(st1->outer.state);
	st2->ipad = ft_memdup(st1->ipad, st2->my_vtable.block_size);
	st2->opad = ft_memdup(st1->opad, st2->my_vtable.block_size);
	return (st2);
}
