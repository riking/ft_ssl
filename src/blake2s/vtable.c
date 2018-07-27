/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:56:32 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 12:25:28 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./blake2s.h"
#include <stdlib.h>

void			blake2s_free(void *state)
{
	free(state);
}

const t_ft_hash_vtable	g_blake2s_256_hash_vtable = {
	&blake2s_256init,
	&blake2s_free,
	&blake2s_g_write,
	&blake2s_finish,
	BLAKE2S_256_OUTPUT_SIZE,
	BLAKE2S_BLOCK_SIZE,
};

const t_ft_hash_vtable	g_blake2s_128_hash_vtable = {
	&blake2s_128init,
	&blake2s_free,
	&blake2s_g_write,
	&blake2s_finish,
	BLAKE2S_128_OUTPUT_SIZE,
	BLAKE2S_BLOCK_SIZE,
};
