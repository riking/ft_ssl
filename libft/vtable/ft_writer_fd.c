/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:20:02 by kyork             #+#    #+#             */
/*   Updated: 2018/05/09 17:35:01 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_writer.h"
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

static ssize_t				ft_fdwriter_write(void *state,
		const char *buf, size_t len)
{
	int fd;

	fd = (int)(uintptr_t)state;
	return (write(fd, buf, len));
}

static void					ft_fdwriter_free(void *state)
{
	(void)state;
}

t_ft_writer					ft_writer_fd(int fd)
{
	uintptr_t	state;

	state = fd;
	return (t_ft_writer){&g_ft_fdwriter_vtable, (void*)state};
}

const t_ft_writer_vtable	g_ft_fdwriter_vtable = {
	&ft_fdwriter_write,
	&ft_fdwriter_free,
};
