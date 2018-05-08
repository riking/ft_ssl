/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:12:20 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 17:26:31 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoding.h"
#include <libft.h>
#include <ft_printf.h>

#include <stdlib.h>

size_t		hex_length(void *opts, const t_u8 *src, size_t len)
{
	(void)opts;
	(void)src;
	return (len * 2);
}

void		hex_encode(void *o, const t_u8 *src, size_t len, t_u8 *dest)
{
	t_hex_opts	*opts;
	size_t		idx;
	char		*dst;
	const char	*fmt;

	opts = o;
	dst = (char*)dest;
	fmt = "%02x";
	if (opts && opts->uppercase)
		fmt = "%02X";
	idx = 0;
	while (idx < len)
	{
		ft_snprintf(dst + (idx * 2), 2 + 1, fmt, src[idx]);
		idx++;
	}
}

static const t_u8	g_hex_alphabet[256] = {
	['0'] = 0x80,
	['1'] = 0x1,
	['2'] = 0x2,
	['3'] = 0x3,
	['4'] = 0x4,
	['5'] = 0x5,
	['6'] = 0x6,
	['7'] = 0x7,
	['8'] = 0x8,
	['9'] = 0x9,
	['a'] = 0xa,
	['b'] = 0xb,
	['c'] = 0xc,
	['d'] = 0xd,
	['e'] = 0xe,
	['f'] = 0xf,
	['A'] = 0xa,
	['B'] = 0xb,
	['C'] = 0xc,
	['D'] = 0xd,
	['E'] = 0xe,
	['F'] = 0xf,
};

#define DECODED(idx, val) (void)(dest ? (dest[(idx++)] = (val)) : idx++, (val))

ssize_t		hex_decode(void *opts, const t_u8 *src, size_t len,
						t_u8 *dest)
{
	const t_u8	*s;
	t_u8		partial;
	bool		phase;
	size_t		idx;

	(void)opts;
	idx = 0;
	partial = 0;
	s = src - 1;
	phase = false;
	while (++s < src + len)
	{
		if (IS_SPACE(*s))
			continue ;
		if (!g_hex_alphabet[*s])
			return (-1);
		if (phase)
			DECODED(idx, (g_hex_alphabet[*s] & 0xF) | partial);
		else
			partial = (g_hex_alphabet[*s] & 0xF) << 4;
	}
	if (phase)
		return (-1);
	return (idx);
}

const char	*g_hex_options = "-x u or -x U: use uppercase";

void		*hex_process_opt(void *o, const char *option)
{
	t_hex_opts	*opts;

	if (!option)
		return (ft_memalloc(sizeof(t_hex_opts)));
	opts = o;
	if (0 == ft_strcmp(option, "U") || 0 == ft_strcmp(option, "u"))
	{
		opts->uppercase = true;
	}
	else
		return (NULL);
	return (opts);
}
