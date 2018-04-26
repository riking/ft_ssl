/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_roundconf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:00:22 by kyork             #+#    #+#             */
/*   Updated: 2018/04/25 21:13:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_core.h"
#include <libft.h>
#include <stdalign.h>

#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define AA (st->s[(0 + (o->rot & 3)) % 4])
#define BB (st->s[(1 + (o->rot & 3)) % 4])
#define CC (st->s[(2 + (o->rot & 3)) % 4])
#define DD (st->s[(3 + (o->rot & 3)) % 4])

static void				md5_roundop(t_md5state *st, t_md5hack *x,
									const t_roundconf *c, const t_roundop *o)
{
	AA = BB + ROL(AA + c->f(BB, CC, DD) + x->x[o->k] + g_md5_tvals[o->i], o->s);
}

void					md5_round(t_md5state *st, t_md5hack *x,
									const t_roundconf *c)
{
	size_t	idx;

	idx = 0;
	while (idx < 16)
	{
		md5_roundop(st, x, c, &c->ops[idx]);
		idx++;
	}
}

const t_roundconf		g_md5_rounds[4] = {
	{{
			{0, 0, 7, 1}, {1, 1, 12, 2}, {2, 2, 17, 3}, {3, 3, 22, 4},
			{0, 4, 7, 5}, {1, 5, 12, 6}, {2, 6, 17, 7}, {3, 7, 22, 8},
			{0, 8, 7, 9}, {1, 9, 12, 10}, {2, 10, 17, 11}, {3, 11, 22, 12},
			{0, 12, 7, 13}, {1, 13, 12, 14}, {2, 14, 17, 15}, {3, 15, 22, 16},
		}, md5_func_f},
	{{
			{0, 1, 5, 17}, {1, 6, 9, 18}, {2, 11, 14, 19}, {3, 0, 20, 20},
			{0, 5, 5, 21}, {1, 10, 9, 22}, {2, 15, 14, 23}, {3, 4, 20, 24},
			{0, 9, 5, 25}, {1, 14, 9, 26}, {2, 3, 14, 27}, {3, 8, 20, 28},
			{0, 13, 5, 29}, {1, 2, 9, 30}, {2, 7, 14, 31}, {3, 12, 20, 32},
		}, md5_func_g},
	{{
			{0, 5, 4, 33}, {1, 8, 11, 34}, {2, 11, 16, 35}, {3, 14, 23, 36},
			{0, 1, 4, 37}, {1, 4, 11, 38}, {2, 7, 16, 39}, {3, 10, 23, 40},
			{0, 13, 4, 41}, {1, 0, 11, 42}, {2, 3, 16, 43}, {3, 6, 23, 44},
			{0, 9, 4, 45}, {1, 12, 11, 46}, {2, 15, 16, 47}, {3, 2, 23, 48},
		}, md5_func_h},
	{{
			{0, 0, 6, 49}, {1, 7, 10, 50}, {2, 14, 15, 51}, {3, 5, 21, 52},
			{0, 12, 6, 53}, {1, 3, 10, 54}, {2, 10, 15, 55}, {3, 1, 21, 56},
			{0, 8, 6, 57}, {1, 15, 10, 58}, {2, 6, 15, 59}, {3, 13, 21, 60},
			{0, 4, 6, 61}, {1, 11, 10, 62}, {2, 2, 15, 63}, {3, 9, 21, 64},
		}, md5_func_i},
};

const t_u32				g_md5_tvals[65] = {
	0x0,
	0xd76aa478,
	0xe8c7b756,
	0x242070db,
	0xc1bdceee,
	0xf57c0faf,
	0x4787c62a,
	0xa8304613,
	0xfd469501,
	0x698098d8,
	0x8b44f7af,
	0xffff5bb1,
	0x895cd7be,
	0x6b901122,
	0xfd987193,
	0xa679438e,
	0x49b40821,
	0xf61e2562,
	0xc040b340,
	0x265e5a51,
	0xe9b6c7aa,
	0xd62f105d,
	0x2441453,
	0xd8a1e681,
	0xe7d3fbc8,
	0x21e1cde6,
	0xc33707d6,
	0xf4d50d87,
	0x455a14ed,
	0xa9e3e905,
	0xfcefa3f8,
	0x676f02d9,
	0x8d2a4c8a,
	0xfffa3942,
	0x8771f681,
	0x6d9d6122,
	0xfde5380c,
	0xa4beea44,
	0x4bdecfa9,
	0xf6bb4b60,
	0xbebfbc70,
	0x289b7ec6,
	0xeaa127fa,
	0xd4ef3085,
	0x4881d05,
	0xd9d4d039,
	0xe6db99e5,
	0x1fa27cf8,
	0xc4ac5665,
	0xf4292244,
	0x432aff97,
	0xab9423a7,
	0xfc93a039,
	0x655b59c3,
	0x8f0ccc92,
	0xffeff47d,
	0x85845dd1,
	0x6fa87e4f,
	0xfe2ce6e0,
	0xa3014314,
	0x4e0811a1,
	0xf7537e82,
	0xbd3af235,
	0x2ad7d2bb,
	0xeb86d391,
};
