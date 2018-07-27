/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_opts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:30:13 by kyork             #+#    #+#             */
/*   Updated: 2018/05/22 14:14:49 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoding.h"

#include <libft.h>

#define ALPHABET_C "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ALPHABET_S ALPHABET_C "0123456789+/"
#define ALPHABET_U ALPHABET_C "0123456789-_"

static t_b64_opts	g_default_opts = {
	ALPHABET_S, 0,
};

const char			*g_b64_options = ""
"-x pad or -x padding: use padding (=)\n"
"-x raw or -x nopad: do not emit padding (=) (default)\n"
"-x std: use standard encoding (63 64 is +/)\n"
"-x url or -x urlsafe: use URL-safe encoding (63 64 is -_)\n";

t_b64_opts			*b64_fixopts(t_b64_opts *opts)
{
	if (!opts)
		return (&g_default_opts);
	if (!opts->alphabet)
	{
		opts->alphabet = ALPHABET_S;
	}
	return (opts);
}

void				*b64_process_opt(void *o, const char *opt)
{
	t_b64_opts *opts;

	if (!opt)
	{
		opts = ft_memalloc(sizeof(t_b64_opts));
		*opts = g_default_opts;
		return (opts);
	}
	opts = o;
	if (0 == ft_strcmp(opt, "raw") || 0 == ft_strcmp(opt, "nopad"))
		opts->use_padding = false;
	else if (0 == ft_strcmp(opt, "pad") || 0 == ft_strcmp(opt, "padding"))
		opts->use_padding = true;
	else if (0 == ft_strcmp(opt, "std"))
		opts->alphabet = ALPHABET_S;
	else if (0 == ft_strcmp(opt, "url") || 0 == ft_strcmp(opt, "urlsafe"))
		opts->alphabet = ALPHABET_U;
	else
		return (NULL);
	return (opts);
}
