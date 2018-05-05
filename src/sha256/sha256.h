/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:16:32 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 16:24:08 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

# include "../commontypes.h"
# include <stdalign.h>

int					ft_ssl_sha256(int argc, char **argv);

/*
** in bytes
*/
# define SHA256_BLOCK_SIZE 64
# define SHA256_OUTPUT_SIZE 32

# define AU32_BYTE alignas(t_u32) t_u8

/*
** sha256state holds a partially computed hash. copying OK.
** buf contains unprocessed bytes, bufsz is the number of valid bytes inside
*/
typedef struct		s_sha256state {
	t_u32		s[8];
	AU32_BYTE	buf[SHA256_BLOCK_SIZE];
	int			bufsz;
	t_u64		len;
}					t_sha256state;

/*
** sha256_core: exposed API
*/
t_sha256state		sha256_init(void);
void				sha256_write(t_sha256state *st, t_u8 *buf, size_t len);
void				sha256_finish(t_sha256state *st, t_u8 *outbuf);

/*
** sha256_core: internal
*/
void				sha256_block(t_sha256state *st, t_u8 *buf);

#endif
