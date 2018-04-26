/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:23:04 by kyork             #+#    #+#             */
/*   Updated: 2016/10/21 19:55:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_PRINTF_COUNT_ERR
#include "ft_printf_private.h"
#undef FT_PRINTF_COUNT_ERR

void		ft_printf_reset_parse(t_printf_parse *parse)
{
	parse->func = 0;
	parse->min_width = 0;
	parse->precis = 0;
	parse->flags = 0;
	parse->lenmod = PF_SIZE_NONE;
	parse->spec = '\0';
	parse->sign = '\0';
	parse->ox = '\0';
}

void		ft_printf_setup_parse(
				t_printf_parse *parse,
				t_printer printer,
				size_t max_print)
{
	parse->printer = printer;
	parse->max_print = max_print;
	parse->used_size = 0;
}

ssize_t		ft_do_printf(
		const char *fmt,
		va_list args,
		t_printf_parse *parse)
{
	ssize_t			count;
	ssize_t			fmtlen;

	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			ft_printf_reset_parse(parse);
			fmtlen = ft_printf_parse(fmt, parse, args);
			if (parse->func)
			{
				fmt += fmtlen;
				COUNT(count, parse->func(parse, args));
				continue;
			}
		}
		COUNT(count, parse->printer(parse, *fmt++));
	}
	return (count);
}
