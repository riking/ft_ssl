/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:27:56 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 12:45:13 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blake2s.h"
#include <libft.h>
#define MIN(a, b) ({typeof(a)_a=(a);typeof(b)_b=(b);(_a<_b)?_a:_b;})

#define ADJ_SZ(buf, len, adj) buf += adj; len -= adj;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define LEU32(buf) (*(t_u32*)(buf))
#elif __BYTE__ORDER == __ORDER_BIG_ENDIAN__
# define LEU32(buf) (__builtin_bswap32(*(t_u32*)(buf)))
#else
# error Unsupported endianness define
#endif

/*
** important - do NOT write the final block here!
*/

void			blake2s_write(t_blake2s_state *st, t_u8 *buf, size_t len)
{
	size_t	tmpsz;

	if (st->bufsz)
	{
		tmpsz = MIN((size_t)(BLAKE2S_BLOCK_SIZE - st->bufsz), len);
		ft_memcpy(st->buf + st->bufsz, buf, tmpsz);
		st->bufsz += tmpsz;
		ADJ_SZ(buf, len, tmpsz);
		if (len > 0 && (st->bufsz == BLAKE2S_BLOCK_SIZE))
			blake2s_block(st, st->buf, 0);
		if (len > 0 && (st->bufsz == BLAKE2S_BLOCK_SIZE))
			st->bufsz = 0;
	}
	while (len > BLAKE2S_BLOCK_SIZE)
	{
		blake2s_block(st, buf, 0);
		ADJ_SZ(buf, len, BLAKE2S_BLOCK_SIZE);
	}
	ft_memcpy(st->buf, buf, len);
	st->bufsz += len;
}

ssize_t			blake2s_g_write(void *state, t_u8 *buf, size_t len)
{
	t_blake2s_state	*st;

	st = state;
	blake2s_write(st, buf, len);
	return (len);
}

void			blake2s_finish(void *state, t_u8 *outbuf)
{
	t_blake2s_state	st;
	t_u8			buf[BLAKE2S_BLOCK_SIZE];
	size_t			remaining;
	int				i;

	st = *(t_blake2s_state*)state;
	ft_bzero(buf, BLAKE2S_BLOCK_SIZE);
	ft_memcpy(buf, st.buf, st.bufsz);
	remaining = BLAKE2S_BLOCK_SIZE - st.bufsz;
	if (st.c[0] < remaining)
		st.c[1]--;
	st.c[0] -= remaining;
	blake2s_block(&st, buf, 0xFFFFFFFFUL);
	i = -1;
	while (++i < 8)
		LEU32(&buf[i * 4]) = st.h[i];
	ft_memcpy(outbuf, buf, st.out_size);
}
