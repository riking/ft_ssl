/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:27:18 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 14:43:06 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include "get_next_line_private.h"

#define GNC_EOF -2

static int	gnc_next(t_gnl_fd *s)
{
	unsigned char	ch;
	ssize_t			read_ret;

	if (0 != ft_ary_remove_mul(&s->chars, 0, (size_t)(s->nl_off + 1)))
		return (-1);
	if (s->chars.item_count == 0)
	{
		read_ret = gnl_read(s);
		if (read_ret == -1)
			return (-1);
		if (read_ret == 0)
			return (GNC_EOF);
	}
	ch = ((unsigned char*)s->chars.ptr)[0];
	s->nl_off = 0;
	return (ch);
}

int			get_next_char(const int fd)
{
	t_gnl_fd	*s;
	size_t		i;
	int			ret;

	if (fd < 0)
		return (-1);
	s = NULL;
	i = 0;
	while (i < g_bufio_state.fds.item_count)
		if ((s = (t_gnl_fd*)ft_ary_get(&g_bufio_state.fds, i++))->fd == fd)
			break ;
	if (s == NULL || s->fd != fd)
		if (!(s = gnl_setup(&g_bufio_state, fd)))
			return (-1);
	ret = gnc_next(s);
	if (ret == GNC_EOF)
	{
		errno = 0;
		return (-1);
	}
	return (ret);
}
