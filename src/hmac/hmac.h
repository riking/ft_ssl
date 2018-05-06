/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 13:28:14 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 14:45:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HMAC_H
# define FT_SSL_HMAC_H

# include "../hash.h"

/*
** callers must free the passed 'base' hash - the hmac makes a copy.
**
** The returned vtable is dynamic and points into the state.
** Do not use the vtable after calling vtable->free.
** Callers also should not inspect the actual 'state' struct.
*/
t_ft_hash				hmac_create(t_ft_hash base,
							const char *key, size_t key_len);

/*
** our block size / output size is variable
** so we need a custom vtable
** - inner is the hash we do streaming writes into
** - outer is never actually written to, it's always cloned in a pristine state
**   this way we can do multiple finish()es
** - ipad, opad are of size my_vtable.block_size
*/

typedef struct			s_hmac_state {
	t_ft_hash_vtable	my_vtable;
	t_ft_hash			inner;
	t_ft_hash			outer;
	t_u8				*ipad;
	t_u8				*opad;
}						t_hmac_state;

void					*hmacg_clone(void *state);
void					hmac_free(void *state);
ssize_t					hmac_write(void *state, t_u8 *buf, size_t len);
void					hmac_finish(void *state, t_u8 *outbuf);

#endif
