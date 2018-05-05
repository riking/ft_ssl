/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:24:19 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:11:04 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./sha256.h"
#include <libft.h>
#define MIN(a, b) ({typeof(a)_a=(a);typeof(b)_b=(b);(_a<_b)?_a:_b;})

#define ADJ_SZ(buf, len, stlen, adj) buf += adj; len -= adj; stlen += adj;

/*
** TODO verify
*/

void			sha256_write(t_sha256state *st, t_u8 *buf, size_t len)
{
	size_t	tmpsz;

	if (st->bufsz)
	{
		tmpsz = MIN((size_t)(SHA256_BLOCK_SIZE - st->bufsz), len);
		ft_memcpy(st->buf + st->bufsz, buf, tmpsz);
		st->bufsz += tmpsz;
		ADJ_SZ(buf, len, st->len, tmpsz);
		if (st->bufsz == SHA256_BLOCK_SIZE)
			sha256_block(st, st->buf);
		if (st->bufsz == SHA256_BLOCK_SIZE)
			st->bufsz = 0;
	}
	while (len >= SHA256_BLOCK_SIZE)
	{
		sha256_block(st, buf);
		ADJ_SZ(buf, len, st->len, SHA256_BLOCK_SIZE);
	}
	ft_memcpy(st->buf, buf, len);
	st->bufsz += len;
	st->len += len;
}

t_sha256state	sha256_init(void)
{
	t_sha256state	st;

	st.s[0] = 0x6A09E667;
	st.s[1] = 0xBB67AE85;
	st.s[2] = 0x3C6EF372;
	st.s[3] = 0xA54FF53A;
	st.s[4] = 0x510E527F;
	st.s[5] = 0x9B05688C;
	st.s[6] = 0x1F83D9AB;
	st.s[7] = 0x5BE0CD19;
	ft_bzero(st.buf, SHA256_BLOCK_SIZE);
	st.bufsz = 0;
	st.len = 0;
	return (st);
}
