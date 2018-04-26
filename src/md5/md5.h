/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:28:53 by kyork             #+#    #+#             */
/*   Updated: 2018/04/26 16:07:22 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_MD5_H
# define FT_SSL_MD5_MD5_H

# include "../commontypes.h"
# include <stdalign.h>

int					ft_ssl_md5(int argc, char **argv);

/*
** in bytes
*/
# define MD5_CHUNK_SIZE 64
# define MD5_OUTPUT_SIZE 16

# define AU32_BYTE alignas(t_u32) t_u8

/*
** md5state holds a partially computed hash. copying OK.
** buf contains unprocessed bytes, bufsz is the number of valid bytes inside
*/
typedef struct		s_md5state {
	t_u32		s[4];
	AU32_BYTE	buf[MD5_CHUNK_SIZE];
	int			bufsz;
	t_u64		len;
}					t_md5state;

/*
** md5_core: exposed API
*/
t_md5state			md5_init(void);
void				md5_write(t_md5state *st, t_u8 *buf, size_t len);
void				md5_finish(t_md5state *st, t_u8 *outbuf);

/*
** md5_core: internal
*/
void				md5_block(t_md5state *st, t_u8 *buf);

#endif
