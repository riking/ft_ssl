/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:43:23 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:27:33 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_core.h"

#define ROLR(x, n) (((x) >> (n)) | ((x) << (32-(n))))
#define SA (w->s[0])
#define SB (w->s[1])
#define SC (w->s[2])
#define SD (w->s[3])
#define SE (w->s[4])
#define SF (w->s[5])
#define SG (w->s[6])
#define SH (w->s[7])

static const t_u32	g_sha256_k[64] = {
	0x428a2f98,
	0x71374491,
	0xb5c0fbcf,
	0xe9b5dba5,
	0x3956c25b,
	0x59f111f1,
	0x923f82a4,
	0xab1c5ed5,
	0xd807aa98,
	0x12835b01,
	0x243185be,
	0x550c7dc3,
	0x72be5d74,
	0x80deb1fe,
	0x9bdc06a7,
	0xc19bf174,
	0xe49b69c1,
	0xefbe4786,
	0x0fc19dc6,
	0x240ca1cc,
	0x2de92c6f,
	0x4a7484aa,
	0x5cb0a9dc,
	0x76f988da,
	0x983e5152,
	0xa831c66d,
	0xb00327c8,
	0xbf597fc7,
	0xc6e00bf3,
	0xd5a79147,
	0x06ca6351,
	0x14292967,
	0x27b70a85,
	0x2e1b2138,
	0x4d2c6dfc,
	0x53380d13,
	0x650a7354,
	0x766a0abb,
	0x81c2c92e,
	0x92722c85,
	0xa2bfe8a1,
	0xa81a664b,
	0xc24b8b70,
	0xc76c51a3,
	0xd192e819,
	0xd6990624,
	0xf40e3585,
	0x106aa070,
	0x19a4c116,
	0x1e376c08,
	0x2748774c,
	0x34b0bcb5,
	0x391c0cb3,
	0x4ed8aa4a,
	0x5b9cca4f,
	0x682e6ff3,
	0x748f82ee,
	0x78a5636f,
	0x84c87814,
	0x8cc70208,
	0x90befffa,
	0xa4506ceb,
	0xbef9a3f7,
	0xc67178f2,
};

static void			sha256_schedule(t_sha256work *w, t_u8 *buf)
{
	int				i;
	t_u32			v1;
	t_u32			t1;
	t_u32			v2;
	t_u32			t2;

	i = -1;
	while (++i < 16)
		w->w[i] = (t_u32)(buf[i * 4 + 0]) << 24 | (t_u32)(buf[i * 4 + 1]) << 16
			| (t_u32)(buf[i * 4 + 2]) << 8 | (t_u32)(buf[i * 4 + 3]) << 0;
	while (i < 64)
	{
		v1 = w->w[i - 2];
		t1 = ROLR(v1, 17) ^ ROLR(v1, 19) ^ (v1 >> 10);
		v2 = w->w[i - 15];
		t2 = ROLR(v2, 7) ^ ROLR(v2, 18) ^ (v2 >> 3);
		w->w[i] = t1 + w->w[i - 7] + t2 + w->w[i - 16];
		i++;
	}
}

static void			sha256_round(t_sha256work *w, t_s8 i)
{
	t_u32		t1;
	t_u32		t2;

	t1 = SH + (ROLR(SE, 6) ^ ROLR(SE, 11) ^ ROLR(SE, 25)) + ((SE & SF) ^
			(~SE & SG)) + g_sha256_k[i] + w->w[i];
	t2 = (ROLR(SA, 2) ^ ROLR(SA, 13) ^ ROLR(SA, 22)) + ((SA & SB) ^ (SA
				& SC) ^ (SB & SC));
	SH = SG;
	SG = SF;
	SF = SE;
	SE = SD + t1;
	SD = SC;
	SC = SB;
	SB = SA;
	SA = t1 + t2;
}

void				sha256_block(t_sha256state *st, t_u8 *buf)
{
	t_sha256work	w;
	t_u32			save[8];
	int				i;

	i = -1;
	while (++i < 8)
		save[i] = st->s[i];
	sha256_schedule(&w, buf);
	i = -1;
	while (++i < 8)
		w.s[i] = save[i];
	i = -1;
	while (++i < 64)
		sha256_round(&w, i);
	i = -1;
	while (++i < 8)
	{
		st->s[i] = save[i] + w.s[i];
	}
	return ;
}
