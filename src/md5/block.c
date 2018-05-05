/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 21:01:09 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:15:59 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_core.h"
#include <libft.h>
#include <stdalign.h>

/*
** f, g - these are equivalent but faster constructions
** f: return (x & y) | (~x & z);
** g: return (x & z) | (y & ~z);
*/

t_u32					md5_func_f(t_u32 x, t_u32 y, t_u32 z)
{
	return (((y ^ z) & x) ^ z);
}

t_u32					md5_func_g(t_u32 x, t_u32 y, t_u32 z)
{
	return (((x ^ y) & z) ^ y);
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
	md5_round(st, x, &g_md5_rounds[0]);
	md5_round(st, x, &g_md5_rounds[1]);
	md5_round(st, x, &g_md5_rounds[2]);
	md5_round(st, x, &g_md5_rounds[3]);
	st->s[0] += save[0];
	st->s[1] += save[1];
	st->s[2] += save[2];
	st->s[3] += save[3];
}
