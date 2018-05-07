/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blake2b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:18:08 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 16:31:49 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_BLAKE2B_H
# define FT_SSL_BLAKE2B_H

# include "../hash.h"

/*
** output size is variable, but -512 is used here
*/

# define BLAKE2B_BLOCK_SIZE 128
# define BLAKE2B_512_OUTPUT_SIZE 64
# define BLAKE2B_384_OUTPUT_SIZE 48
# define BLAKE2B_256_OUTPUT_SIZE 32

# define BLAKE2B_KEY_SIZE 64

typedef struct			s_blake2b_state {
	t_u64		h[8];
	t_u64		c[2];
	size_t		out_size;
	t_u8		buf[BLAKE2B_BLOCK_SIZE];
	int			bufsz;
	t_u8		key[BLAKE2B_BLOCK_SIZE];
	int			keysz;
}						t_blake2b_state;

/*
**
*/

t_ft_hash				blake2b_init_key(int hash_size,
							t_u8 *key, size_t key_len);

void					*blake2b_512init(void *state);
void					*blake2b_384init(void *state);
void					*blake2b_256init(void *state);
void					blake2b_free(void *state);
ssize_t					blake2b_g_write(void *state, t_u8 *buf, size_t len);
void					blake2b_finish(void *state, t_u8 *outbuf);

void					blake2b_write(t_blake2b_state *state,
							t_u8 *buf, size_t len);
void					blake2b_block(t_blake2b_state *state, t_u8 *block,
							t_u64 flag);
/*
** const t_ft_hash_vtable	g_blake2b_512_hash_vtable;
** const t_ft_hash_vtable	g_blake2b_384_hash_vtable;
** const t_ft_hash_vtable	g_blake2b_256_hash_vtable;
*/

void					blake2b_reset(t_blake2b_state *state);

typedef const t_s8		t_blake2b_sigma[16];

typedef struct			s_blake2b_roundconf {
	int					a;
	int					b;
	int					c;
	int					d;
	int					xi;
	int					yi;
}						t_blake2b_roundconf;

typedef struct			s_blake2b_roundvars {
	t_blake2b_sigma	*s;
	t_u64			*m;
	t_u64			*v;
}						t_blake2b_roundvars;

#endif
