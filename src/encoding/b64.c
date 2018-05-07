/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:16:45 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 16:22:32 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoding.h"

#include <libft.h>

#define ALPHABET_C "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ALPHABET_S ALPHABET_C "0123456789+/"
#define ALPHABET_U ALPHABET_C "0123456789-_"

#define CEILDIV(a, b) (((a) + (b) - 1) / (b))

/*
** note - different defaults for command line (zeroed) and code (g_default)
*/

static t_b64_opts	g_default_opts = {
	ALPHABET_S, 0, true,
};

size_t				b64_length(void *o, const t_u8 *src, size_t len)
{
	t_b64_opts	*opts;
	size_t		by;

	opts = o;
	by = CEILDIV(len, 3) * 4;
	if (!opts->use_padding && (len % 3) == 1)
		by -= 2;
	else if (!opts->use_padding && (len % 3) == 2)
		by -= 1;
	if (opts->line_length > 0)
		by += 2 * (size_t)CEILDIV(by, opts->line_length);
	return (by);
}

static int			wr_group(t_b64_opts *opts, t_u32 val, t_u8 *dst, int *scratch)
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
	*scratch += 4;
	if (opts->line_length > 0 && *scratch >= opts->line_length)
	{
		*d++ = '\r';
		*d++ = '\n';
		*scratch = 0;
	}
	return (((t_u8*)d) - dst);
}

void				b64_encode(void *o, const t_u8 *src, size_t len, t_u8 *dst)
{
	t_b64_opts *opts;
	t_u32		temp;
	size_t		sidx;
	int			scratch;

	opts = o ? (t_b64_opts*)o : &g_default_opts;
	if (!opts->alphabet)
		opts->alphabet = ALPHABET_S;
	sidx = 0;
	scratch = 0;
	while (sidx + 3 < len)
	{
		temp = (src[sidx] << 16) | (src[sidx + 1] << 8) | (src[sidx + 2]);
		dst += wr_group(opts, temp, dst, &scratch);
		sidx += 3;
	}
	if (len - sidx == 1)
		temp = (src[sidx] << 16) | (1 << 25);
	else if (len - sidx == 2)
		temp = (src[sidx] << 16) | (src[sidx + 1] << 8) | (1 << 26);
	if (len - sidx != 0)
		dst += wr_group(opts, temp, dst, &scratch);
	if (opts->line_length > 0 && scratch)
		ft_memcpy(dst, "\r\n", 2);
}

const char			*b64_options = ""
"-x pad or -x =: use padding (=)\n"
"-x nopad or -x raw: do not emit padding (=) (default)\n"
"-x url or -x urlsafe: use URL-safe encoding (-_ instead of +/)\n"
"-x wrap64: line-wrap output every 64 encoded characters\n"
"-x wrap76 or -x wrap: line-wrap output to 80 columns\n";

void				*b64_process_opt(void *o, const char *opt)
{
	t_b64_opts *opts;

	if (!opt)
	{
		opts = ft_memalloc(sizeof(t_b64_opts));
		*opts = g_default_opts;
		return (opts);
	}
	opts = o;
	if (0 == ft_strcmp(opt, "nopad") || 0 == ft_strcmp(opt, "raw"))
		opts->use_padding = false;
	else if (0 == ft_strcmp(opt, "pad") || 0 == ft_strcmp(opt, "="))
		opts->use_padding = true;
	else if (0 == ft_strcmp(opt, "url") || 0 == ft_strcmp(opt, "urlsafe"))
		opts->alphabet = ALPHABET_U;
	else if (0 == ft_strcmp(opt, "wrap64"))
		opts->line_length = 64;
	else if (0 == ft_strcmp(opt, "wrap76") || 0 == ft_strcmp(opt, "wrap"))
		opts->line_length = 76;
	else
		return (NULL);
	return (opts);
}
