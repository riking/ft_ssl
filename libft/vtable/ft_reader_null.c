/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:12:46 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:13:41 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reader.h"

static ssize_t				ft_nullreader_read(void *state,
		char *buf, size_t len)
{
	(void)state;
	(void)buf;
	(void)len;
	return (0);
}

static void					ft_nullreader_free(void *state)
{
	(void)state;
}

t_ft_reader					ft_reader_null(void)
{
	return (t_ft_reader){&g_ft_nullreader_vtable, NULL};
}

const t_ft_reader_vtable	g_ft_nullreader_vtable = {
	&ft_nullreader_read,
	&ft_nullreader_free,
};
