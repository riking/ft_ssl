/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_core.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:50:01 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 16:25:28 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_CORE_H
# define FT_SSL_MD5_CORE_H

# include "md5.h"

typedef struct				s_roundop {
	int		rot;
	int		k;
	int		s;
	int		i;
}							t_roundop;

typedef t_u32				(t_md5_roundfunc)(t_u32, t_u32, t_u32);

typedef struct				s_roundconf {
	t_roundop			ops[16];
	t_md5_roundfunc		*f;
}							t_roundconf;

/*
** x86 makes faster code if we just treat the input as an array of uint32s
*/
typedef struct				s_md5hack {
	t_u32		x[MD5_BLOCK_SIZE / 4];
}							t_md5hack;

extern const t_u32			g_md5_tvals[65];

extern const t_roundconf	g_md5_rounds[4];

void						md5_round(t_md5state *st, t_md5hack *x,
									const t_roundconf *c);

t_u32						md5_func_f(t_u32 x, t_u32 y, t_u32 z);
t_u32						md5_func_g(t_u32 x, t_u32 y, t_u32 z);
t_u32						md5_func_h(t_u32 x, t_u32 y, t_u32 z);
t_u32						md5_func_i(t_u32 x, t_u32 y, t_u32 z);

#endif
