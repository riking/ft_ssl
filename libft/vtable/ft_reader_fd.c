/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:07:53 by kyork             #+#    #+#             */
/*   Updated: 2018/05/09 17:34:04 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_reader.h"
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

static ssize_t				ft_fdreader_read(void *state,
		char *buf, size_t len)
{
	int fd;

	fd = (int)(uintptr_t)state;
	return (read(fd, buf, len));
}

static void					ft_fdreader_free(void *state)
{
	(void)state;
}

t_ft_reader					ft_reader_fd(int fd)
{
	uintptr_t	state;

	state = fd;
	return (t_ft_reader){&g_ft_fdreader_vtable, (void*)state};
}

const t_ft_reader_vtable	g_ft_fdreader_vtable = {
	&ft_fdreader_read,
	&ft_fdreader_free,
};
