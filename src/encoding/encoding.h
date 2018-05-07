/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 14:59:08 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 16:22:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_ENCODING_H
# define FT_SSL_ENCODING_H

# include "../commontypes.h"
# include <stddef.h>
# include <stdbool.h>

/*
** vtable contract:
** a NULL value for 'opts' is always valid.
** length - take options and a buffer, return how many bytes are required for
**          output.
** encode - take options, a source and a destination buffer. encode the source
**          data into the destination.
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

size_t				hex_length(void *opts, const t_u8 *src, size_t len);
void				hex_encode(void *opts, const t_u8 *src,
						size_t len, t_u8 *dst);
void				*hex_process_opt(void *opts, const char *option);
extern const char	*hex_options;

typedef struct		s_b64_opts {
	const char		*alphabet;
	int				line_length;
	bool			use_padding;
}					t_b64_opts;

size_t				b64_length(void *opts, const t_u8 *src,
						size_t len);
void				b64_encode(void *opts, const t_u8 *src,
						size_t len, t_u8 *dst);
void				*b64_process_opt(void *opts, const char *option);
extern const char	*b64_options;

#endif
