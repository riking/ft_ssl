/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 21:01:09 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 14:50:00 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_core.h"
#include <libft.h>
#include <ft_printf.h>
#include <stdalign.h>

t_u32					md5_func_f(t_u32 x, t_u32 y, t_u32 z)
{
	return (((y ^ z) & x) ^ z);
	//return (x & y) | (~x & z);
}

t_u32					md5_func_g(t_u32 x, t_u32 y, t_u32 z)
{
	return (((x ^ y) & z) ^ y);
	//return (x & z) | (y & ~z);
}

t_u32					md5_func_h(t_u32 x, t_u32 y, t_u32 z)
{
	return (x ^ y ^ z);
}

t_u32					md5_func_i(t_u32 x, t_u32 y, t_u32 z)
{
	return (y ^ (x | ~z));
}

/*
** md5hack is an attempt to treat the passed pointer as uint32's.
** if we don't have the right alignment, just make a copy.
*/

void					md5_block(t_md5state *st, t_u8 *buf)
{
	t_md5hack	*x;
	t_md5hack	copy;
	t_u32		save[4];

	if ((((uintptr_t)buf) & (alignof(t_u32) - 1)) == 0)
		x = (t_md5hack*)buf;
	else
	{
		ft_memcpy((t_u8*)&copy, buf, MD5_CHUNK_SIZE);
		x = &copy;
	}
	ft_memcpy(save, st->s, sizeof(t_u32) * 4);
	ft_printf("[CHUNK] %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n",
			x->x[0], x->x[1], x->x[2], x->x[3], x->x[4], x->x[5], x->x[6], x->x[7], x->x[8], x->x[9], x->x[10], x->x[11], x->x[12], x->x[13], x->x[14], x->x[15]);
	ft_printf("[STATE0] %08X %08X %08X %08X\n", st->s[0], st->s[1], st->s[2], st->s[3]);
	md5_round(st, x, &g_md5_rounds[0]);
	ft_printf("[STATE1] %08X %08X %08X %08X\n", st->s[0], st->s[1], st->s[2], st->s[3]);
	md5_round(st, x, &g_md5_rounds[1]);
	ft_printf("[STATE2] %08X %08X %08X %08X\n", st->s[0], st->s[1], st->s[2], st->s[3]);
	md5_round(st, x, &g_md5_rounds[2]);
	ft_printf("[STATE3] %08X %08X %08X %08X\n", st->s[0], st->s[1], st->s[2], st->s[3]);
	md5_round(st, x, &g_md5_rounds[3]);
	ft_printf("[STATE4] %08X %08X %08X %08X\n", st->s[0], st->s[1], st->s[2], st->s[3]);
	st->s[0] += save[0];
	st->s[1] += save[1];
	st->s[2] += save[2];
	st->s[3] += save[3];
}
