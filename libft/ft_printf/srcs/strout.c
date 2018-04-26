/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:03:27 by kyork             #+#    #+#             */
/*   Updated: 2016/10/24 08:27:12 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_PRINTF_COUNT_ERR
#include "ft_printf_private.h"

/*
** [left_padding] [s] [right_padding]
*/

static ssize_t	padding(t_printf_parse *parse, ssize_t length, char padchr)
{
	ssize_t count;

	count = 0;
	while (count < length)
	{
		COUNT(count, parse->printer(parse, padchr));
	}
	return (count);
}

int				ft_printf_digout(t_printf_parse *parse, char *s, size_t strlen)
{
	size_t		realsz;
	ssize_t		count;
	size_t		i;

	realsz = strlen + (parse->sign ? 1 : 0) + (parse->ox ? 2 : 0);
	count = 0;
	if (!HAVE_FLAG(parse, PF_FLAG_ALIGN_LEFT | PF_FLAG_ZERO_PAD))
		COUNT(count, padding(parse, parse->min_width - realsz, ' '));
	if (parse->sign)
		COUNT(count, parse->printer(parse, parse->sign));
	if (parse->ox)
		COUNT(count, parse->printer(parse, '0'));
	if (parse->ox)
		COUNT(count, parse->printer(parse, parse->ox));
	if (!HAVE_FLAG(parse, PF_FLAG_ALIGN_LEFT) &&
			HAVE_FLAG(parse, PF_FLAG_ZERO_PAD))
		COUNT(count, padding(parse, parse->min_width - realsz, '0'));
	i = 0;
	while (i < strlen)
		COUNT(count, parse->printer(parse, s[i++]));
	if (parse->min_width > strlen && HAVE_FLAG(parse, PF_FLAG_ALIGN_LEFT))
		COUNT(count, padding(parse, parse->min_width - realsz, ' '));
	return (count);
}

/*
** flags handled: min_width, ZERO_PAD, ALIGN_LEFT
**
** ALIGN_LEFT overrides ZERO_PAD, aka right padding is always ' '
*/

int				ft_printf_strout(t_printf_parse *parse, char *s, size_t strlen)
{
	ssize_t		count;
	size_t		i;

	count = 0;
	if (!HAVE_FLAG(parse, PF_FLAG_ALIGN_LEFT))
		COUNT(count, padding(parse, parse->min_width - strlen,
					HAVE_FLAG(parse, PF_FLAG_ZERO_PAD) ? '0' : ' '));
	i = 0;
	while (i < strlen)
	{
		COUNT(count, parse->printer(parse, s[i]));
		i++;
	}
	if (parse->min_width > strlen && HAVE_FLAG(parse, PF_FLAG_ALIGN_LEFT))
		COUNT(count, padding(parse, parse->min_width - strlen, ' '));
	return (count);
}
