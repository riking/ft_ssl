/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_chr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:24:13 by kyork             #+#    #+#             */
/*   Updated: 2018/05/09 17:37:24 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_PRINTF_COUNT_ERR
#include "ft_printf_private.h"
#undef FT_PRINTF_COUNT_ERR

#include <wchar.h>
#include <stdlib.h>

#ifdef _MSC_VER
# error This file only functions properly for UTF-32 wide characters
#endif

/*
** MacOS has a signed wint_t, but linux does not. (??)
*/

#ifdef linux
# include <stdint.h>
# define WINT int32_t
#else
# define WINT wint_t
#endif

static int		putchar_unicode(char *b, uint32_t cp)
{
	char *buf;

	buf = b;
	if (cp > 0x1FFFFF)
		return (-1);
	if (cp < 128)
		*buf++ = (char)cp;
	else
	{
		if (cp >= 0x10000)
			*buf++ = ((char)((cp >> (6 * 3)) | 0xF0));
		if (cp >= 0x10000)
			*buf++ = ((char)((cp >> (6 * 2) & 0x3F) | 0x80));
		if (cp >= 0x0800 && cp < 0x10000)
			*buf++ = ((char)((cp >> (6 * 2)) | 0xE0));
		if (cp >= 0x0800)
			*buf++ = ((char)((cp >> (6 * 1) & 0x3F) | 0x80));
		if (cp >= 0x0080 && cp < 0x0800)
			*buf++ = ((char)((cp >> (6 * 1)) | 0xC0));
		if (cp >= 0x0080)
			*buf++ = ((char)((cp >> (6 * 0) & 0x3F) | 0x80));
	}
	return (buf - b);
}

int				ft_printf_c(t_printf_parse *parse, va_list args)
{
	WINT	c;
	char	buf[5];
	int		len;

	if (parse->lenmod == PF_SIZE_L)
	{
		c = va_arg(args, WINT);
		if (c < 0)
			return (-1);
		len = putchar_unicode(buf, c);
	}
	else
	{
		c = (unsigned char)va_arg(args, int);
		buf[0] = (char)c;
		len = 1;
	}
	buf[len] = 0;
	return (ft_printf_strout(parse, buf, len));
}

static ssize_t	ft_printf_wstrlen(wchar_t *wstr)
{
	ssize_t		wlen;

	wlen = 0;
	while (wstr[wlen])
		wlen++;
	return (wlen);
}

static ssize_t	wstr_out(t_printf_parse *parse, wchar_t *wstr)
{
	char		*buf;
	char		*b;
	char		*last;
	ssize_t		i;

	i = 0;
	buf = malloc(ft_printf_wstrlen(wstr) * 4);
	if (!buf)
		return (-1);
	b = buf;
	while (wstr[i])
	{
		last = b;
		COUNTX(b, free(buf), putchar_unicode(b, wstr[i]));
		if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS) && parse->precis < (b - buf))
		{
			b = last;
			break ;
		}
		i++;
	}
	i = ft_printf_strout(parse, buf, (b - buf));
	free(buf);
	return (i);
}

int				ft_printf_s(t_printf_parse *parse, va_list args)
{
	wchar_t		*ws;
	char		*s;
	ssize_t		count;

	count = 0;
	if (parse->lenmod == PF_SIZE_L)
	{
		ws = va_arg(args, wchar_t*);
		if (ws == NULL)
			ws = L"(null)";
		count = wstr_out(parse, ws);
	}
	else
	{
		s = va_arg(args, char*);
		if (s == NULL)
			s = "(null)";
		while (s[count])
			count++;
		if (HAVE_FLAG(parse, PF_FLAG_HAVE_PRECIS) && parse->precis < count)
			count = parse->precis;
		count = ft_printf_strout(parse, s, count);
	}
	return (count);
}
