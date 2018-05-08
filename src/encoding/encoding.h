/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 14:59:08 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 20:02:02 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_ENCODING_H
# define FT_SSL_ENCODING_H

# include "../commontypes.h"
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

/*
** vtable contract:
** a NULL value for 'opts' is always valid.
** enclen - take options and a buffer, return how many bytes are required for
**          encoding.
** encode - take options, a source and a destination buffer.  encode the source
**          data into the destination.
** decode - take options, a source and a destination buffer.  Decode as much of
**          the source data as possible into the destination, returning the
**          number of destination bytes written or -1 on error.  If the
**          destination is NULL, just check for errors and count bytes.
** process_opt - if option == NULL, ignore opts.  Allocate a new options
**               struct with malloc(3) and return it.  Otherwise, *opts is a
**               pointer returned from a previous call to this function.
**               If the option is recognized, apply changes to the struct and
**               return opts.  If the option is not recognized, return NULL.
**               The caller is responsible for calling free(3).
*/

typedef struct		s_hex_opts {
	bool			uppercase;
}					t_hex_opts;

size_t				hex_enclen(void *opts, const t_u8 *src, size_t len);
size_t				hex_encode(void *opts, const t_u8 *src, size_t len,
						t_u8 *dst);
ssize_t				hex_decode(void *opts, const t_u8 *src, size_t len, 
						t_u8 *dst);
extern const char	*g_hex_options;

typedef struct		s_b64_opts {
	const char		*alphabet;
	bool			use_padding;
}					t_b64_opts;

t_b64_opts			*b64_fixopts(t_b64_opts *opts);
size_t				b64_enclen(void *opts, const t_u8 *src, size_t len);
size_t				b64_encode(void *opts, const t_u8 *src, size_t len,
						t_u8 *dst);
ssize_t				b64_decode(void *opts, const t_u8 *src, size_t len, 
						t_u8 *dst);
extern const char	*g_b64_options;

typedef struct		s_b64_decoder {

}					t_b64_decoder;

typedef struct		s_ft_encoder_vtable {
	size_t			(*enclen)(void *, const t_u8 *, size_t);
	void			(*encode)(void *, const t_u8 *, size_t, t_u8 *);
	ssize_t			(*decode)(void *, const t_u8 *, size_t, t_u8 *);
	const char		*options_help;
}					t_ft_encoder_vtable;


#endif
