/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmain.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:57:15 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 15:05:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HASHMAIN_HASHMAIN_H
# define FT_SSL_HASHMAIN_HASHMAIN_H

# include "../hash.h"
# include <libft.h>
# include <stdbool.h>

typedef enum			e_hashmain_outfmt {
	HASHMAIN_FMT_RICH,
	HASHMAIN_FMT_COREUTILS,
	HASHMAIN_FMT_PLAIN,
}						t_hashmain_outfmt;

/*
** ops - t_array<t_hashop>
** hmac_key - from argv, do not free
*/
typedef struct			s_flags {
	t_ft_hash				alg;
	const char				*name;
	const char				*name_rich;
	const char				*hmac_key;
	t_array					ops;
	t_hashmain_outfmt		outfmt;
	bool					stdin_copy;
	bool					with_colons;
}						t_flags;

typedef struct			s_hashop {
	const char			*filename;
	bool				is_string;
}						t_hashop;

int						hashmain_onflag(void *data,
							const char *flagname, const char *next);
int						hashmain_onarg(void *data, const char *arg);
void					hashmain_setup_hmac(t_flags *flags);

int						ft_ssl_hashmain(int argc, char **argv);

int						hashmain_do_hash(t_flags *flags, t_hashop *op);
int						hashmain_hash_fd(t_flags *flags, t_ft_hash *h,
							int fd, bool tee_stdout);
int						hashmain_run(t_flags *flags);

#endif
