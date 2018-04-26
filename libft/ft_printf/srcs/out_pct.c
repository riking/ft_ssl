/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_pct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:48:33 by kyork             #+#    #+#             */
/*   Updated: 2016/10/24 08:35:20 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"

int				ft_printf_percent(t_printf_parse *parse, va_list args)
{
	char c;

	(void)args;
	c = parse->spec;
	if (!c)
		return (0);
	return (ft_printf_strout(parse, &c, 1));
}

static int64_t	sext(int64_t n)
{
	return (n);
}

uint64_t		ft_printf_get_int_arg(
		t_printf_parse *parse,
		bool sign,
		va_list args)
{
	if (sign && parse->lenmod == PF_SIZE_HH)
		return (sext((int8_t)va_arg(args, int)));
	if (!sign && parse->lenmod == PF_SIZE_HH)
		return ((uint64_t)(uint8_t)va_arg(args, unsigned int));
	if (sign && parse->lenmod == PF_SIZE_H)
		return (sext((int16_t)va_arg(args, int)));
	if (!sign && parse->lenmod == PF_SIZE_H)
		return ((uint64_t)(uint16_t)va_arg(args, unsigned int));
	if (sign && (parse->lenmod == PF_SIZE_NONE || parse->lenmod == PF_SIZE_LD))
		return (sext((int32_t)va_arg(args, int)));
	if (!sign && (parse->lenmod == PF_SIZE_NONE || parse->lenmod == PF_SIZE_LD))
		return ((uint64_t)(uint32_t)va_arg(args, unsigned int));
	if (sign && (parse->lenmod == PF_SIZE_L || parse->lenmod == PF_SIZE_LL ||
				parse->lenmod == PF_SIZE_J || parse->lenmod == PF_SIZE_Z))
		return (sext(va_arg(args, long)));
	if (!sign && (parse->lenmod == PF_SIZE_L || parse->lenmod == PF_SIZE_LL ||
				parse->lenmod == PF_SIZE_J || parse->lenmod == PF_SIZE_Z))
		return ((uint64_t)va_arg(args, unsigned long));
	return (0);
}
