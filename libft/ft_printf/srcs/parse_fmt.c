/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:43:04 by kyork             #+#    #+#             */
/*   Updated: 2016/11/08 15:05:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FT_PRINTF_PARSE_C
#include "ft_printf_private.h"
#undef FT_PRINTF_PARSE_C

#include <stdint.h>
#include <stdlib.h>

static const t_specifiers	g_specifiers[] = {
	{ft_printf_percent, '%', false},

	{ft_printf_d, 'd', false},
	{ft_printf_d, 'i', false},
	{ft_printf_d, 'D', true},
	{ft_printf_u, 'u', false},
	{ft_printf_u, 'U', true},
	{ft_printf_o, 'o', false},
	{ft_printf_o, 'O', true},

	{ft_printf_x, 'x', false},
	{ft_printf_x, 'X', false},
	{ft_printf_x, 'p', true},
	{ft_printf_c, 'c', false},
	{ft_printf_c, 'C', true},
	{ft_printf_s, 's', false},
	{ft_printf_s, 'S', true},
};

static const char			*g_specifiers_match = "%" "diDuUoO" "xXpcCsS";

static const t_modifiers	g_modifiers[] = {
	{PF_SIZE_H, sizeof(short), 'h', DOUBLEFLAG_CAN},
	{PF_SIZE_HH, sizeof(char), 'h', DOUBLEFLAG_DID},
	{PF_SIZE_L, sizeof(long), 'l', DOUBLEFLAG_CAN},
	{PF_SIZE_LL, sizeof(long long), 'l', DOUBLEFLAG_DID},
	{PF_SIZE_LD, sizeof(long double), 'L', DOUBLEFLAG_NONE},
	{PF_SIZE_J, sizeof(intmax_t), 'j', DOUBLEFLAG_NONE},
	{PF_SIZE_Z, sizeof(size_t), 'z', DOUBLEFLAG_NONE},
};

static const char			*g_modifiers_match = "hhllLjz";
static const int			g_modifiers_idx_l = 2;

static const t_fmtflags		g_flags[] = {
	{PF_FLAG_ZERO_PAD, '0'},
	{PF_FLAG_ALTERNATE, '#'},
	{PF_FLAG_ALIGN_LEFT, '-'},
	{PF_FLAG_SIGN_ALWAYS | PF_FLAG_SIGN_PLUS, '+'},
	{PF_FLAG_THOUS_SEP, '\''},
	{PF_FLAG_SIGN_ALWAYS, ' '},
	{PF_FLAG_HAVE_PRECIS, '.'},
	{PF_FLAG_SSE_SEP_COMMA, ','},
	{PF_FLAG_SSE_SEP_SEMI, ';'},
	{PF_FLAG_SSE_SEP_COLON, ':'},
	{PF_FLAG_SSE_SEP_UNDER, '_'},
};

static const char			*g_flags_match = "0#-+\' .,;:_";
static const char			*g_number_match = "*0123456789";

static size_t				mod_size(t_printf_lenmod m)
{
	int i;

	if (m == PF_SIZE_NONE)
		return (0);
	i = -1;
	while (++i < ARRAYLEN(g_modifiers))
	{
		if (g_modifiers[i].flag == m)
			return (g_modifiers[i].bytes);
	}
	return (0);
}

static void					do_modifier(
		const char *fmt,
		t_printf_parse *flags,
		va_list args,
		ssize_t i)
{
	if (flags->lenmod == g_modifiers[i].flag &&
			g_modifiers[i].doubled == DOUBLEFLAG_CAN &&
			g_modifiers[i + 1].doubled == DOUBLEFLAG_DID)
	{
		flags->lenmod = g_modifiers[i + 1].flag;
	}
	else if (mod_size(flags->lenmod) < mod_size(g_modifiers[i].flag))
	{
		flags->lenmod = g_modifiers[i].flag;
	}
	(void)fmt;
	(void)args;
}

ssize_t						ft_printf_parse(
		const char *fmtptr,
		t_printf_parse *flags,
		va_list args)
{
	ssize_t		i;
	const char	*fmt;

	fmt = fmtptr;
	while (*++fmt)
	{
		if ((i = ft_printf_strichr(g_modifiers_match, *fmt)) != -1)
			do_modifier(fmt, flags, args, i);
		else if ((i = ft_printf_strichr(g_number_match, *fmt)) != -1)
			ft_printf_numflag(&fmt, flags, args);
		else if ((i = ft_printf_strichr(g_flags_match, *fmt)) != -1)
			flags->flags |= g_flags[i].mask;
		else if ((i = ft_printf_strichr(g_specifiers_match, *fmt)) != -2)
		{
			flags->func = (i == -1) ? &ft_printf_percent : g_specifiers[i].func;
			flags->spec = *fmt;
			if (g_specifiers[i].flag_l)
				do_modifier(0, flags, args, g_modifiers_idx_l);
			return ((fmt + 1) - fmtptr);
		}
	}
	flags->func = &ft_printf_percent;
	flags->spec = *fmt;
	return ((fmt) - fmtptr);
}
