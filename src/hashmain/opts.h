/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:57:15 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 19:55:02 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HASHMAIN_OPTS_H
# define FT_SSL_HASHMAIN_OPTS_H

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
	t_ft_hash_vtable	*alg;
	const char			*name;
	const char			*name_rich;
	const char			*hmac_key;
	t_array				ops;
	t_hashmain_outfmt	outfmt;
	bool				stdin_copy;
}						t_flags;

typedef struct			s_hashop {
	const char			*filename;
	bool				is_string;
}						t_hashop;

int						hashmain_onflag(void *data,
							const char *flagname, const char *next);
int						hashmain_onarg(void *data, const char *arg);

int						hashmain_run(t_flags *flags);

#endif
