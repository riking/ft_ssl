/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:56:32 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 16:58:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./blake2b.h"
#include <stdlib.h>

void			blake2b_free(void *state)
{
	free(state);
}

const t_ft_hash_vtable	g_blake2b_512_hash_vtable = {
	&blake2b_512init,
	&blake2b_free,
	&blake2b_g_write,
	&blake2b_finish,
	BLAKE2B_512_OUTPUT_SIZE,
	BLAKE2B_BLOCK_SIZE,
};

const t_ft_hash_vtable	g_blake2b_384_hash_vtable = {
	&blake2b_384init,
	&blake2b_free,
	&blake2b_g_write,
	&blake2b_finish,
	BLAKE2B_512_OUTPUT_SIZE,
	BLAKE2B_BLOCK_SIZE,
};

const t_ft_hash_vtable	g_blake2b_256_hash_vtable = {
	&blake2b_256init,
	&blake2b_free,
	&blake2b_g_write,
	&blake2b_finish,
	BLAKE2B_512_OUTPUT_SIZE,
	BLAKE2B_BLOCK_SIZE,
};
