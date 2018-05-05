/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:34:07 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:02:10 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_CORE_H
# define FT_SSL_SHA256_CORE_H

# include "./sha256.h"

typedef struct		s_sha256work {
	t_u32		w[64];
	t_u32		s[8];
}					t_sha256work;

/*
** void				sha256_block(t_sha256state *st, t_u8 *buf);
** void				sha256_schedule(t_sha256work *w, t_u8 *buf);
** void				sha256_round(t_sha256work *w, t_s8 i);
*/

#endif
