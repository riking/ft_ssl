/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:52:14 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:10:18 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./md5.h"
#include <libft.h>
#define MIN(a, b) ({typeof(a)_a=(a);typeof(b)_b=(b);(_a<_b)?_a:_b;})

#define ADJ_SZ(buf, len, stlen, adj) buf += adj; len -= adj; stlen += adj;

/*
** TODO verify
*/

void			md5_write(t_md5state *st, t_u8 *buf, size_t len)
{
	size_t	tmpsz;

	if (st->bufsz)
	{
		tmpsz = MIN((size_t)(MD5_CHUNK_SIZE - st->bufsz), len);
		ft_memcpy(st->buf + st->bufsz, buf, tmpsz);
		st->bufsz += tmpsz;
		ADJ_SZ(buf, len, st->len, tmpsz);
		if (st->bufsz == MD5_CHUNK_SIZE)
			md5_block(st, st->buf);
		if (st->bufsz == MD5_CHUNK_SIZE)
			st->bufsz = 0;
	}
	while (len >= MD5_CHUNK_SIZE)
	{
		md5_block(st, buf);
		ADJ_SZ(buf, len, st->len, MD5_CHUNK_SIZE);
	}
	ft_memcpy(st->buf, buf, len);
	st->bufsz += len;
	st->len += len;
}

t_md5state		md5_init(void)
{
	t_md5state	st;

	st.s[0] = 0x67452301;
	st.s[1] = 0xEFCDAB89;
	st.s[2] = 0x98BADCFE;
	st.s[3] = 0x10325476;
	ft_bzero(st.buf, MD5_CHUNK_SIZE);
	st.bufsz = 0;
	st.len = 0;
	return (st);
}
