/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_progname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 11:31:06 by kyork             #+#    #+#             */
/*   Updated: 2016/11/10 13:40:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*g_progname;

void		ft_set_progname(char *argv0)
{
	g_progname = ft_basename(argv0);
}

const char	*ft_progname(void)
{
	return (g_progname);
}
