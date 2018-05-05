/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:26:47 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:06:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HASH_H
# define FT_SSL_HASH_H

# include "commontypes.h"
# include <sys/types.h>

/*
** vtable for hash functions.
** write() will never fail.
*/

typedef struct					s_ft_hash_vtable {
	void		*(*init)(void);
	void		(*free)(void *state);
	ssize_t		(*write)(void *state, t_u8 *buf, size_t len);
	size_t		output_size;
	void		(*finish)(void *state, t_u8 *outbuf);
}					t_ft_hash_vtable;

typedef struct					s_ft_hash {
	t_ft_hash_vtable	*vtable;
	void				*state;
}								t_ft_hash;

typedef struct					s_ft_hash_name {
	t_ft_hash_vtable	*vtable;
	const char			*name;
	const char			*name_rich;
}								t_ft_hash_name;

extern const t_ft_hash_vtable	g_md5_hash_vtable;
extern const t_ft_hash_vtable	g_sha256_hash_vtable;
extern const t_ft_hash_vtable	g_hmac_hash_vtable;

extern const t_ft_hash_name		g_hash_list[];

#endif
