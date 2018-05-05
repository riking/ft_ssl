/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:30:03 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:20:22 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <libft.h>
#include <stdlib.h>

static void		sha256_writelen(t_sha256state *st)
{
	t_u64		len;
	int			i;
	t_u8		buf[SHA256_BLOCK_SIZE];

	ft_bzero(buf, sizeof(buf));
	buf[0] = 0x80;
	len = st->len;
	if ((len % 64) < 56)
		sha256_write(st, buf, 56 - (len % 64));
	else
		sha256_write(st, buf, 64 + 56 - (len % 64));
	len <<= 3;
	i = -1;
	while (++i < 8)
		buf[i] = (t_u8)(len >> (56 - 8 * i));
	sha256_write(st, buf, 8);
}

void			sha256_finish(t_sha256state *st1, t_u8 *outbuf)
{
	t_sha256state	st;
	int				i;

	st = *st1;
	sha256_writelen(&st);
	if (st.bufsz != 0)
		abort();
	i = 0;
	while (i < (SHA256_OUTPUT_SIZE / 4))
	{
		outbuf[i * 4 + 0] = (t_u8)(st.s[i] >> 24);
		outbuf[i * 4 + 1] = (t_u8)(st.s[i] >> 16);
		outbuf[i * 4 + 2] = (t_u8)(st.s[i] >> 8);
		outbuf[i * 4 + 3] = (t_u8)(st.s[i] >> 0);
		i++;
	}
	return ;
}
