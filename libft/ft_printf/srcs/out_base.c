/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 14:09:17 by kyork             #+#    #+#             */
/*   Updated: 2016/10/24 08:35:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"
#include <stdlib.h>

static ssize_t	ft_printf_itoa_oct(
		char *buf,
		t_printf_parse *parse,
		uint64_t nbr)
{
	uint64_t	pow_oct;
	uint64_t	n;
	size_t		poctdigits;
	size_t		i;

	n = nbr;
	i = 0;
	while (parse->precis > 22 + i)
		buf[i++] = '0';
	pow_oct = 01000000000000000000000UL;
	poctdigits = 22;
	while (pow_oct > n && pow_oct > 0 && poctdigits-- > parse->precis)
		pow_oct /= 010;
	while (pow_oct > 0)
	{
		buf[i++] = '0' + (char)(n / pow_oct);
		n %= pow_oct;
		pow_oct /= 010;
	}
	if (nbr == 0 && !HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		buf[i++] = '0';
	return (i);
}

static ssize_t	ft_printf_itoa_hex(
		char *buf,
		char *base,
		t_printf_parse *parse,
		uint64_t nbr)
{
	uint64_t	pow_hex;
	uint64_t	n;
	size_t		phexdigits;
	size_t		i;

	n = nbr;
	i = 0;
	while (parse->precis > 16 + i)
		buf[i++] = '0';
	pow_hex = 0x1000000000000000UL;
	phexdigits = 16;
	while (pow_hex > n && pow_hex > 0 && phexdigits-- > parse->precis)
		pow_hex /= 0x10;
	while (pow_hex > 0)
	{
		buf[i++] = base[(n / pow_hex)];
		n %= pow_hex;
		pow_hex /= 0x10;
	}
	if (nbr == 0 && !HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		buf[i++] = '0';
	return (i);
}

int				ft_printf_o(t_printf_parse *parse, va_list args)
{
	uint64_t	n;
	ssize_t		count;
	char		*buf;

	if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		parse->flags &= ~PF_FLAG_ZERO_PAD;
	if (parse->precis > 22)
		buf = malloc(parse->precis + 1);
	else
		buf = malloc(23);
	if (!buf)
		return (-1);
	n = ft_printf_get_int_arg(parse, false, args);
	buf[0] = 0;
	count = ft_printf_itoa_oct(buf, parse, n);
	if (HAVE_FLAG(parse, PF_FLAG_ALTERNATE) && buf[0] != '0')
		parse->sign = '0';
	count = ft_printf_digout(parse, buf, count);
	free(buf);
	return (count);
}

int				ft_printf_x(t_printf_parse *parse, va_list args)
{
	uint64_t	n;
	ssize_t		count;
	char		*buf;

	if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		parse->flags &= ~PF_FLAG_ZERO_PAD;
	if (parse->precis > 16)
		buf = malloc(parse->precis + 2);
	else
		buf = malloc(18);
	if (!buf)
		return (-1);
	n = ft_printf_get_int_arg(parse, false, args);
	if (parse->spec == 'p' || (n != 0 && HAVE_FLAG(parse, PF_FLAG_ALTERNATE)))
		parse->ox = (parse->spec == 'X') ? 'X' : 'x';
	if (parse->spec == 'X')
		count = ft_printf_itoa_hex(buf, "0123456789ABCDEF", parse, n);
	else
		count = ft_printf_itoa_hex(buf, "0123456789abcdef", parse, n);
	count = ft_printf_digout(parse, buf, count);
	free(buf);
	return (count);
}
