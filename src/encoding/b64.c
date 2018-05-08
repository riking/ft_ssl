/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:16:45 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 17:45:21 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoding.h"

#include <libft.h>

#define CEILDIV(a, b) (((a) + (b) - 1) / (b))

size_t				b64_enclen(void *o, const t_u8 *src, size_t len)
{
	t_b64_opts	*opts;
	size_t		by;

	opts = o;
	by = CEILDIV(len, 3) * 4;
	if (!opts->use_padding && (len % 3) == 1)
		by -= 2;
	else if (!opts->use_padding && (len % 3) == 2)
		by -= 1;
	return (by);
}

static int			wr_group(t_b64_opts *opts, t_u32 val, t_u8 *dst)
{
	char		*d;
	int			shift;

	d = (char*)dst;
	*d++ = opts->alphabet[(val >> 18) & 0x3F];
	*d++ = opts->alphabet[(val >> 12) & 0x3F];
	if ((val & (1 << 25)))
		*d++ = opts->alphabet[(val >> 6) & 0x3F];
	else if (opts->use_padding)
		*d++ = '=';
	if ((val & (1 << 25)) || ((val & (1 << 26))))
		*d++ = opts->alphabet[(val >> 0) & 0x3F];
	else if (opts->use_padding)
		*d++ = '=';
	return (((t_u8*)d) - dst);
}

size_t				b64_encode(void *o, const t_u8 *src, size_t len, t_u8 *dst)
{
	t_b64_opts *opts;
	t_u8		*d;
	t_u32		val;
	size_t		sidx;

	opts = b64_fixopts((t_b64_opts*)o);
	d = dst;
	sidx = 0;
	while (sidx + 3 < len)
	{
		val = (src[sidx] << 16) | (src[sidx + 1] << 8) | (src[sidx + 2]);
		dst += wr_group(opts, val, dst);
		sidx += 3;
	}
	if (sidx == len)
		return (dst - d);
	val = (src[sidx] << 16) | (1 << 25);
	if (len - sidx == 2)
		val = (src[sidx] << 16) | (src[sidx + 1] << 8) | (1 << 26);
	dst += wr_group(opts, val, dst);
	return (dst - d);
}

ssize_t				b64_decode(void *o, const t_u8 *src, size_t len, t_u8 *dst)
{
	t_b64_opts	*opts;

	opts = b64_fixopts(o);
}
