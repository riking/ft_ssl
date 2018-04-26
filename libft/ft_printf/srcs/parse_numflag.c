/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numflag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 16:05:02 by kyork             #+#    #+#             */
/*   Updated: 2016/10/24 08:27:35 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_private.h"

/*
** TODO(kyork): $ selection for star args
*/

static void			star_arg(
		const char **fmt,
		t_printf_parse *parse,
		unsigned int *field,
		va_list args)
{
	int tmp;

	(void)fmt;
	tmp = va_arg(args, int);
	if (tmp < 0)
	{
		if (!HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
			parse->flags |= PF_FLAG_ALIGN_LEFT;
		else
		{
			parse->precis = 0;
			parse->flags &= ~PF_FLAG_HAVE_PRECIS;
			return ;
		}
	}
	if (tmp == -2147483648)
		tmp = 2147483647;
	else if (tmp < 0)
		tmp = -tmp;
	*field = (unsigned int)tmp;
}

static int			fmt_tonbr(const char **fmt, long *result)
{
	int any;

	*result = 0;
	any = 0;
	while ('0' <= **fmt && **fmt <= '9')
	{
		*result = *result * 10 + (**fmt - '0');
		(*fmt)++;
		any = 1;
	}
	return (any);
}

void				ft_printf_numflag(
		const char **fmt,
		t_printf_parse *parse,
		va_list args)
{
	unsigned int	*field;
	long			result;

	field = HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS) ?
		&parse->precis : &parse->min_width;
	if (**fmt == '0' && !HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS))
		parse->flags |= PF_FLAG_ZERO_PAD;
	else
	{
		if (**fmt == '*')
			star_arg(fmt, parse, field, args);
		else
		{
			if (fmt_tonbr(fmt, &result))
				(*fmt)--;
			*field = (int)result;
		}
	}
}
