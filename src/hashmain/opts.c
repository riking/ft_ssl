/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:30:14 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 19:59:19 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "opts.h"
#include "../optparse.h"

#include <libft.h>
#include <ft_printf.h>

static int		hashmain_onflag2(t_flags *flags,
			const char *flag, const char *nxt)
{
	if (0 == ft_strcmp(flag, "hmac"))
	{
		flags->hmac_key = nxt;
		return (1);
	}
	else
		return (-1);
	return (0);
}

int				hashmain_onflag(void *data, const char *flag, const char *nxt)
{
	t_flags		*flags;
	char		*tmp;
	t_hashop	op;

	flags = data;
	if (0 == ft_strcmp(flag, "p"))
		flags->stdin_copy = true;
	else if (0 == ft_strcmp(flag, "q"))
		flags->outfmt = HASHMAIN_FMT_PLAIN;
	else if (0 == ft_strcmp(flag, "r"))
	{
		if (flags->outfmt < HASHMAIN_FMT_PLAIN)
			flags->outfmt = HASHMAIN_FMT_COREUTILS;
	}
	else if (0 == ft_strcmp(flag, "s"))
	{
		op = (t_hashop){nxt, true};
		ft_ary_append(&flags->ops, &op);
		return (1);
	}
	else
		return (hashmain_onflag2(flags, flag, nxt));
	return (0);
}

int				hashmain_onarg(void *data, const char *arg)
{
	t_flags		*flags;
	t_hashop	op;

	flags = data;
	op = (t_hashop){arg, false};
	ft_ary_append(&flags->ops, &op);
	return (0);
}

static int		hashmain_flag_init(t_flags *flags, char *alg)
{
	size_t	idx;

	idx = 0;
	flags->alg = NULL;
	while (g_hash_list[idx++].vtable)
		if (0 == ft_strcmp(alg, g_hash_list[idx - 1].name))
		{
			flags->alg = g_hash_list[idx - 1].vtable;
			flags->name = g_hash_list[idx - 1].name;
			flags->name_rich = g_hash_list[idx - 1].name_rich;
		}
	if (!flags->alg)
	{
		ft_dprintf(2, "%s: hash: error: unknown algorithm name '%s'\n",
				ft_progname(), alg);
		return (1);
	}
	flags->hmac_key = NULL;
	flags->ops = ft_ary_create(sizeof(t_hashop));
	flags->outfmt = HASHMAIN_FMT_RICH;
	return (0);
}

const char		*g_hashmain_help = "options are\n"
	"-p         copy stdin to stdout and append the checksum\n"
	"-q         quiet mode (do not print leader before file hash)\n"
	"-r         coreutils output format\n"
	"-s string  hash the given string\n"
	"-hmac key  create a HMAC digest with given key\n"
	"\n"
	"provide filename parameters to hash them\n"
	"default operation (no flags, no filenames) is to hash stdin\n";

int				ft_ssl_hashmain(int argc, char **argv)
{
	t_flags		flags;
	t_optparse	optparse;
	int			r;

	if (hashmain_flag_init(&flags, argv[1]) < 0)
		return (2);
	optparse.data = &flags;
	optparse.onflag = &hashmain_onflag;
	optparse.onarg = &hashmain_onarg;
	if (parse_opts(&optparse, argv + 2) < 0)
	{
		ft_dprintf(2, "%s", g_hashmain_help);
		return (2);
	}
	return (hashmain_run(&flags));
}
