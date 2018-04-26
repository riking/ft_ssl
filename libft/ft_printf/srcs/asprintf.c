/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:23:04 by kyork             #+#    #+#             */
/*   Updated: 2016/10/21 12:48:45 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"
#include <stdlib.h>

int			ft_asprintf(char **ret, const char *fmt, ...)
{
	va_list			args;
	int				len;

	va_start(args, fmt);
	len = ft_vasprintf(ret, fmt, args);
	va_end(args);
	return (len);
}

int			ft_vasprintf(char **ret, const char *fmt, va_list args)
{
	ssize_t			count1;
	ssize_t			count2;
	va_list			clone;
	t_printf_parse	parse;

	*ret = NULL;
	va_copy(clone, args);
	ft_printf_setup_parse(&parse, &ft_printf_printer_noop, -1ULL);
	count1 = ft_do_printf(fmt, clone, &parse);
	va_end(clone);
	if (count1 < 0)
		return (-1);
	*ret = malloc(count1 + 1);
	if (!*ret)
		return (-1);
	ft_printf_setup_parse(&parse, &ft_printf_printer_str, count1 + 1);
	parse.print_data.str.str = *ret;
	count2 = ft_do_printf(fmt, args, &parse);
	(*ret)[parse.used_size] = '\0';
	return ((int)count2);
}
