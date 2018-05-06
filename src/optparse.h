/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 19:21:53 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 15:02:16 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPTPARSE_H
# define FT_SSL_OPTPARSE_H

/*
** data is passed to each callback
** onflag - flagname is passed the flag without the leading "-". return 0 for
**   success, -1 for abort, and positive to consume the next argument.
** onarg - called with each non-option argument. return 0 for OK, -1 = abort
** no special processing for "-" or "--", to mirror openssl.
*/
typedef struct	s_optparse {
	void	*data;
	int		(*onflag)(void *data, const char *flagname, const char *next);
	int		(*onarg)(void *data, const char *arg);
}				t_optparse;

/*
** Pass this function (argv + 2) - strip out the binary name and subcommand
** name.
*/

int				parse_opts(t_optparse *opts, char **argv1);

#endif
