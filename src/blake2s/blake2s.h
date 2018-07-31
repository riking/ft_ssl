/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blake2s.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:18:08 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 13:09:46 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_BLAKE2S_H
# define FT_SSL_BLAKE2S_H

# include "../hash.h"

# define BLAKE2S_BLOCK_SIZE 64
# define BLAKE2S_256_OUTPUT_SIZE 32
# define BLAKE2S_128_OUTPUT_SIZE 16

# define BLAKE2S_KEY_SIZE 32

typedef struct			s_blake2s_state {
	t_u32		h[8];
	t_u32		c[2];
	size_t		out_size;
	t_u8		buf[BLAKE2S_BLOCK_SIZE];
	int			bufsz;
	t_u8		key[BLAKE2S_BLOCK_SIZE];
	int			keysz;
}						t_blake2s_state;

t_ft_hash				blake2s_init_key(int hash_size,
							t_u8 *key, size_t key_len);

void					*blake2s_256init(void *state);
void					*blake2s_128init(void *state);
void					blake2s_free(void *state);
ssize_t					blake2s_g_write(void *state, t_u8 *buf, size_t len);
void					blake2s_finish(void *state, t_u8 *outbuf);

void					blake2s_write(t_blake2s_state *state,
							t_u8 *buf, size_t len);
void					blake2s_block(t_blake2s_state *state, t_u8 *block,
							t_u32 flag);

void					blake2s_reset(t_blake2s_state *state);

typedef const t_s8		t_blake2s_sigma[16];

typedef struct			s_blake2s_roundconf {
	int					a;
	int					b;
	int					c;
	int					d;
	int					xi;
	int					yi;
}						t_blake2s_roundconf;

#endif
