/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:26:52 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 12:43:41 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blake2s.h"

#include <libft.h>
#include <stdlib.h>

static void				blake2s_init(t_blake2s_state *st, int hash_size,
								t_u8 *key, size_t key_len)
{
	st->out_size = hash_size;
	if (key_len > BLAKE2S_KEY_SIZE)
		abort();
	st->keysz = key_len;
	ft_bzero(st->key, BLAKE2S_BLOCK_SIZE);
	ft_memcpy(st->key, key, key_len);
	blake2s_reset(st);
}

t_ft_hash				blake2s_init_key(int hash_size,
								t_u8 *key, size_t key_len)
{
	t_ft_hash		ret;
	t_blake2s_state	*st;

	if (hash_size == BLAKE2S_256_OUTPUT_SIZE)
		ret.vtable = &g_blake2s_256_hash_vtable;
	else if (hash_size == BLAKE2S_128_OUTPUT_SIZE)
		ret.vtable = &g_blake2s_128_hash_vtable;
	else
		abort();
	st = ft_memalloc(sizeof(t_blake2s_state));
	blake2s_init(st, hash_size, key, key_len);
	ret.state = st;
	return (ret);
}

void					*blake2s_256init(void *state)
{
	t_blake2s_state *st1;
	t_blake2s_state *st2;

	st2 = ft_memalloc(sizeof(t_blake2s_state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	blake2s_init(st2, BLAKE2S_256_OUTPUT_SIZE, NULL, 0);
	return (st2);
}

void					*blake2s_128init(void *state)
{
	t_blake2s_state *st1;
	t_blake2s_state *st2;

	st2 = ft_memalloc(sizeof(t_blake2s_state));
	if (state)
	{
		st1 = state;
		*st2 = *st1;
		return (st2);
	}
	blake2s_init(st2, BLAKE2S_128_OUTPUT_SIZE, NULL, 0);
	return (st2);
}
