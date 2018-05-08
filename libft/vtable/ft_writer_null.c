/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:22:51 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:23:36 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_writer.h"

static ssize_t				ft_nullwriter_write(void *state,
		const char *buf, size_t len)
{
	(void)state;
	(void)buf;
	(void)len;
	return (0);
}

static void					ft_nullwriter_free(void *state)
{
	(void)state;
}

t_ft_writer					ft_writer_null(void)
{
	return (t_ft_writer){&g_ft_nullwriter_vtable, NULL};
}

const t_ft_writer_vtable	g_ft_nullwriter_vtable = {
	&ft_nullwriter_write,
	&ft_nullwriter_free,
};
