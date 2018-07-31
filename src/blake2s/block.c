/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:32:09 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 12:56:23 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blake2s.h"

#include <libft.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define LEU32(buf) (*(t_u32*)(buf))
#elif __BYTE__ORDER == __ORDER_BIG_ENDIAN__
# define LEU32(buf) (__builtin_bswap32(*(t_u32*)(buf)))
#else
# error Unsupported endianness define
#endif

static const t_blake2s_sigma		g_precomputed[10] = {
	{0, 2, 4, 6, 1, 3, 5, 7, 8, 10, 12, 14, 9, 11, 13, 15},
	{14, 4, 9, 13, 10, 8, 15, 6, 1, 0, 11, 5, 12, 2, 7, 3},
	{11, 12, 5, 15, 8, 0, 2, 13, 10, 3, 7, 9, 14, 6, 1, 4},
	{7, 3, 13, 11, 9, 1, 12, 14, 2, 5, 4, 15, 6, 10, 0, 8},
	{9, 5, 2, 10, 0, 7, 4, 15, 14, 11, 6, 3, 1, 12, 8, 13},
	{2, 6, 0, 8, 12, 10, 11, 3, 4, 7, 15, 1, 13, 5, 14, 9},
	{12, 1, 14, 4, 5, 15, 13, 10, 0, 6, 9, 8, 7, 3, 2, 11},
	{13, 7, 12, 3, 11, 14, 1, 9, 5, 15, 8, 2, 0, 4, 6, 10},
	{6, 14, 11, 0, 15, 9, 3, 8, 12, 13, 1, 10, 2, 7, 4, 5},
	{10, 8, 7, 1, 2, 4, 6, 5, 15, 9, 3, 13, 11, 14, 12, 0},
};

static const t_u32					g_blake2s_iv[8] = {
	0x6a09e667,
	0xbb67ae85,
	0x3c6ef372,
	0xa54ff53a,
	0x510e527f,
	0x9b05688c,
	0x1f83d9ab,
	0x5be0cd19,
};

static const t_blake2s_roundconf	g_blake2s_rounds[8] = {
	{0, 4, 8, 12, 0, 4},
	{1, 5, 9, 13, 1, 5},
	{2, 6, 10, 14, 2, 6},
	{3, 7, 11, 15, 3, 7},
	{0, 5, 10, 15, 8, 12},
	{1, 6, 11, 12, 9, 13},
	{2, 7, 8, 13, 10, 14},
	{3, 4, 9, 14, 11, 15},
};

#define AA v[q->a]
#define BB v[q->b]
#define CC v[q->c]
#define DD v[q->d]
#define XX m[s[q->xi]]
#define YY m[s[q->yi]]

static void							blake2s_roundop1(
		const t_blake2s_roundconf *q, const t_blake2s_sigma s,
		t_u32 *m, t_u32 *v)
{
	AA += XX;
	AA += BB;
	DD ^= AA;
	DD = ((DD << (32 - 16)) | (DD >> 16));
	CC += DD;
	BB ^= CC;
	BB = ((BB << (32 - 12)) | (BB >> 12));
}

static void							blake2s_roundop2(
		const t_blake2s_roundconf *q, const t_blake2s_sigma s,
		t_u32 *m, t_u32 *v)
{
	AA += YY;
	AA += BB;
	DD ^= AA;
	DD = ((DD << (32 - 8)) | (DD >> 8));
	CC += DD;
	BB ^= CC;
	BB = ((BB << (32 - 7)) | (BB >> 7));
}

static void							blake2s_round(
		const t_blake2s_sigma s, t_u32 *m, t_u32 *v)
{
	blake2s_roundop1(&g_blake2s_rounds[0], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[1], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[2], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[3], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[0], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[1], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[2], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[3], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[4], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[5], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[6], s, m, v);
	blake2s_roundop1(&g_blake2s_rounds[7], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[4], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[5], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[6], s, m, v);
	blake2s_roundop2(&g_blake2s_rounds[7], s, m, v);
}

void								blake2s_block(t_blake2s_state *state,
		t_u8 *block, t_u32 flag)
{
	t_u32		m[16];
	t_u32		v[16];
	int			i;

	state->c[0] += BLAKE2S_BLOCK_SIZE;
	if (state->c[0] < BLAKE2S_BLOCK_SIZE)
		state->c[1]++;
	ft_memcpy(&v[0], state->h, 8 * sizeof(t_u32));
	ft_memcpy(&v[8], g_blake2s_iv, 8 * sizeof(t_u32));
	v[12] ^= state->c[0];
	v[13] ^= state->c[1];
	v[14] ^= flag;
	i = -1;
	while (++i < 16)
		m[i] = LEU32(&block[i * 4]);
	i = -1;
	while (++i < 10)
		blake2s_round(g_precomputed[i], m, v);
	i = -1;
	while (++i < 8)
		state->h[i] ^= v[i] ^ v[i + 8];
}

void								blake2s_reset(t_blake2s_state *st)
{
	ft_memcpy(st->h, g_blake2s_iv, sizeof(g_blake2s_iv));
	st->c[0] = 0;
	st->c[1] = 0;
	ft_bzero(st->buf, BLAKE2S_BLOCK_SIZE);
	st->bufsz = 0;
	st->h[0] ^= (t_u32)(st->out_size) | (((t_u32)st->keysz) << 8) |
		(1 << 16) | (1 << 24);
	if (st->keysz)
		blake2s_block(st, st->key, 0);
}
