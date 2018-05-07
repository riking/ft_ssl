/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:26:52 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 16:24:08 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blake2b.h"

#include <libft.h>
#include <stdlib.h>

static void				blake2b_init(t_blake2b_state *st, int hash_size,
								t_u8 *key, size_t key_len)
{
	st->out_size = hash_size;
	if (key_len > BLAKE2B_KEY_SIZE)
		abort();
	st->keysz = key_len;
	ft_bzero(st->key, BLAKE2B_BLOCK_SIZE);
	ft_memcpy(st->key, key, key_len);
	blake2b_reset(st);
}

t_ft_hash				blake2b_init_key(int hash_size,
								t_u8 *key, size_t key_len)
{
	t_ft_hash		ret;
	t_blake2b_state	*st;

	if (hash_size == BLAKE2B_512_OUTPUT_SIZE)
		ret.vtable = &g_blake2b_512_hash_vtable;
	else if (hash_size == BLAKE2B_384_OUTPUT_SIZE)
		ret.vtable = &g_blake2b_384_hash_vtable;
	else if (hash_size == BLAKE2B_256_OUTPUT_SIZE)
		ret.vtable = &g_blake2b_256_hash_vtable;
	else
		abort();
	st = ft_memalloc(sizeof(t_blake2b_state));
	blake2b_init(st, hash_size, key, key_len);
	ret.state = st;
	return (ret);
}

void					*blake2b_512init(void *state)
{
	t_blake2b_state *st1;
	t_blake2b_state *st2;

	st2 = ft_memalloc(sizeof(t_blake2b_state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	blake2b_init(st2, BLAKE2B_512_OUTPUT_SIZE, NULL, 0);
	return (st2);
}

void					*blake2b_384init(void *state)
{
	t_blake2b_state *st1;
	t_blake2b_state *st2;

	st2 = ft_memalloc(sizeof(t_blake2b_state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	blake2b_init(st2, BLAKE2B_384_OUTPUT_SIZE, NULL, 0);
	return (st2);
}

void					*blake2b_256init(void *state)
{
	t_blake2b_state *st1;
	t_blake2b_state *st2;

	st2 = ft_memalloc(sizeof(t_blake2b_state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	blake2b_init(st2, BLAKE2B_256_OUTPUT_SIZE, NULL, 0);
	return (st2);
}
