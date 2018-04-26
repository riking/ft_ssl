/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_dec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 14:08:33 by kyork             #+#    #+#             */
/*   Updated: 2016/10/21 20:59:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_PRINTF_COUNT_ERR
#include "ft_printf_private.h"
#undef FT_PRINTF_COUNT_ERR

#include <stdlib.h>
#include <stdint.h>

static void		do_sign(
		t_printf_parse *parse,
		uint64_t *n,
		bool sign)
{
	bool		sign_bit;

	sign_bit = (*n & 0x8000000000000000ULL) != 0;
	if (sign && sign_bit)
	{
		parse->sign = '-';
		*n = -*n;
	}
	else if (HAVE_FLAG(parse, PF_FLAG_SIGN_ALWAYS))
	{
		parse->sign = (HAVE_FLAG(parse, PF_FLAG_SIGN_PLUS)) ? '+' : ' ';
	}
	else
	{
		parse->sign = '\0';
	}
}

static ssize_t	ft_printf_itoa_basic(
		char *buf,
		t_printf_parse *parse,
		uint64_t nbr)
{
	uint64_t	pow_ten;
	uint64_t	n;
	size_t		ptendigits;
	size_t		i;

	n = nbr;
	i = 0;
	while (parse->precis > 20 + i)
		buf[i++] = '0';
	pow_ten = 10000000000000000000UL;
	ptendigits = 20;
	while (pow_ten > n && pow_ten > 0 && ptendigits-- > parse->precis)
		pow_ten /= 10;
	while (pow_ten > 0)
	{
		buf[i++] = '0' + (char)(n / pow_ten);
		n %= pow_ten;
		pow_ten /= 10;
	}
	if (nbr == 0 && !HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		buf[i++] = '0';
	return (i);
}

int				ft_printf_d(t_printf_parse *parse, va_list args)
{
	uint64_t	n;
	ssize_t		count;
	char		*buf;

	if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		parse->flags &= ~PF_FLAG_ZERO_PAD;
	if (parse->precis > 20)
		buf = malloc(parse->precis + 1);
	else
		buf = malloc(21);
	if (!buf)
		return (-1);
	n = ft_printf_get_int_arg(parse, true, args);
	do_sign(parse, &n, true);
	count = ft_printf_itoa_basic(buf, parse, n);
	count = ft_printf_digout(parse, buf, count);
	free(buf);
	return (count);
}

int				ft_printf_u(t_printf_parse *parse, va_list args)
{
	uint64_t	n;
	ssize_t		count;
	char		*buf;

	if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		parse->flags &= ~PF_FLAG_ZERO_PAD;
	if (parse->precis > 20)
		buf = malloc(parse->precis + 1);
	else
		buf = malloc(21);
	if (!buf)
		return (-1);
	n = ft_printf_get_int_arg(parse, false, args);
	count = ft_printf_itoa_basic(buf, parse, n);
	count = ft_printf_digout(parse, buf, count);
	free(buf);
	return (count);
}
