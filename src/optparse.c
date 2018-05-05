/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:13:09 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:07:14 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./optparse.h"
#include <libft.h>
#include <ft_printf.h>

/*
** mostly taken from ft_ls, but it's different because of course it's different.
** oops now it doesn't resemble that at all.  oh well
*/

int				parse_opts(t_optparse *opts, char **argv1)
{
	int		ac;
	int		r;

	ac = 0;
	while (argv1[ac] && argv1[ac][0] == '-')
	{
		r = opts->onflag(opts->data, argv1[ac] + 1, argv1[ac + 1]);
		if (r < 0)
		{
			ft_dprintf(2, "%s: unrecognized option '%s'\n", argv1[ac],
					ft_progname());
			return (r);
		}
		else
			ac += 1 + ((r == 0) ? 0 : 1);
	}
	while (argv1[ac])
	{
		r = opts->onarg(opts->data, argv1[ac++]);
		if (r < 0)
			return (r);
	}
	return (0);
}
