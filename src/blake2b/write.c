/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:27:56 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 14:27:55 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blake2b.h"
#include <libft.h>
#define MIN(a, b) ({typeof(a)_a=(a);typeof(b)_b=(b);(_a<_b)?_a:_b;})

#define ADJ_SZ(buf, len, adj) buf += adj; len -= adj;

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define LEU64(buf) (*(t_u64*)(buf))
#elif __BYTE__ORDER == __ORDER_BIG_ENDIAN__
# define LEU64(buf) (__builtin_bswap64(*(t_u64*)(buf)))
#else
# error Unsupported endianness define
#endif

/*
** important - do NOT write the final block here!
*/

void			blake2b_write(t_blake2b_state *st, t_u8 *buf, size_t len)
{
	size_t	tmpsz;

	if (st->bufsz)
	{
		tmpsz = MIN((size_t)(BLAKE2B_BLOCK_SIZE - st->bufsz), len);
		ft_memcpy(st->buf + st->bufsz, buf, tmpsz);
		st->bufsz += tmpsz;
		ADJ_SZ(buf, len, tmpsz);
		if (len > 0 && (st->bufsz == BLAKE2B_BLOCK_SIZE))
			blake2b_block(st, st->buf, 0);
		if (len > 0 && (st->bufsz == BLAKE2B_BLOCK_SIZE))
			st->bufsz = 0;
	}
	while (len > BLAKE2B_BLOCK_SIZE)
	{
		blake2b_block(st, buf, 0);
		ADJ_SZ(buf, len, BLAKE2B_BLOCK_SIZE);
	}
	ft_memcpy(st->buf, buf, len);
	st->bufsz += len;
}

ssize_t			blake2b_g_write(void *state, t_u8 *buf, size_t len)
{
	t_blake2b_state	*st;

	st = state;
	blake2b_write(st, buf, len);
	return (len);
}

void			blake2b_finish(void *state, t_u8 *outbuf)
{
	t_blake2b_state	st;
	t_u8			buf[BLAKE2B_BLOCK_SIZE];
	size_t			remaining;
	t_u64			c[2];
	int				i;

	st = *(t_blake2b_state*)state;
	ft_bzero(buf, BLAKE2B_BLOCK_SIZE);
	ft_memcpy(buf, st.buf, st.bufsz);
	remaining = BLAKE2B_BLOCK_SIZE - st.bufsz;
	ft_memcpy(c, st.c, sizeof(t_u64) * 2);
	if (st.c[0] < remaining)
		st.c[1]--;
	st.c[0] -= remaining;
	blake2b_block(&st, buf, 0xFFFFFFFFFFFFFFFFULL);
	i = -1;
	while (++i < 8)
		LEU64(&buf[i * 8]) = st.h[i];
	ft_memcpy(outbuf, buf, st.out_size);
}
