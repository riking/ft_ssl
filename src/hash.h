/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:26:47 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 14:42:47 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HASH_H
# define FT_SSL_HASH_H

# include "commontypes.h"
# include <sys/types.h>

/*
** vtable for hash functions.
** init - allocate and return a new state struct if NULL is passed, else
**        create a clone of the given state struct.
** free - deallocate the given state struct.
** write - add the given data into the hash and return the number of bytes
**         written.
** finish - write the binary form of the hash sum into outbuf.  the state struct
**          remains valid for further writes and must still be freed.
** output_size - number of bytes required for the outbuf of finish().
** block_size - number of bytes the hash processes at a time. not necessary for
**              most consumers.
*/

typedef struct					s_ft_hash_vtable {
	void		*(*init)(void *state);
	void		(*free)(void *state);
	ssize_t		(*write)(void *state, t_u8 *buf, size_t len);
	void		(*finish)(void *state, t_u8 *outbuf);
	size_t		output_size;
	size_t		block_size;
}					t_ft_hash_vtable;

typedef struct					s_ft_hash {
	const t_ft_hash_vtable	*vtable;
	void					*state;
}								t_ft_hash;

typedef struct					s_ft_hash_name {
	const t_ft_hash_vtable	*vtable;
	const char				*name;
	const char				*name_rich;
}								t_ft_hash_name;

extern const t_ft_hash_vtable	g_md5_hash_vtable;
extern const t_ft_hash_vtable	g_sha256_hash_vtable;

extern const t_ft_hash_name		g_hash_list[];

int								ft_ssl_hashmain(int argc, char **argv);

#endif
