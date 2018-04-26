/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:58:06 by kyork             #+#    #+#             */
/*   Updated: 2018/04/26 16:12:23 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <libft.h>
#include <stdlib.h>

static void		md5_writelen(t_md5state *st)
{
	t_u64		len;
	int			i;
	t_u8		buf[MD5_CHUNK_SIZE];

	ft_bzero(buf, sizeof(buf));
	buf[0] = 0x80;
	len = st->len;
	if ((len % 64) < 56) {
		md5_write(st, buf, 56 - (len % 64));
	} else {
		md5_write(st, buf, 64 + 56 - (len % 64));
	}
	len <<= 3;
	i = -1;
	while (++i < 8)
		buf[i] = (t_u8)(len >> (8*i));
	md5_write(st, buf, 8);
}

void			md5_finish(t_md5state *st1, t_u8 *outbuf)
{
	t_md5state	st;
	int			i;

	st = *st1;
	md5_writelen(&st);
	if (st.bufsz != 0)
		abort();
	i = 0;
	while (i < 4)
	{
		outbuf[i*4+0] = (t_u8)(st.s[i] >> 0);
		outbuf[i*4+1] = (t_u8)(st.s[i] >> 8);
		outbuf[i*4+2] = (t_u8)(st.s[i] >> 16);
		outbuf[i*4+3] = (t_u8)(st.s[i] >> 24);
		i++;
	}
	return ;
}
