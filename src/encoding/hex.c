/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 15:12:20 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 16:22:41 by kyork            ###   ########.fr       */
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

const char	*hex_options = "-x u or -x U: use uppercase";

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
