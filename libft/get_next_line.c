/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:34:56 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 14:48:46 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "get_next_line_private.h"
#include <stdlib.h>
#include <unistd.h>

#define GRSZ_A(s) ((s)->chars.item_count + BUFF_SIZE)
#define GRSZ_B(s) ((s)->chars.item_cap * 2)
#define GROW_SIZE(s) MAX(GRSZ_A(s), GRSZ_B(s))

t_gnl_fd		*gnl_setup(t_gnlstate *t, const int fd)
{
	t_gnl_fd	*s;

	if (t->fds.item_count >= t->fds.item_cap || t->fds.item_cap == 1)
		if (0 != ft_ary_grow(&(t->fds), MAX(4UL, t->fds.item_cap * 2)))
			return (NULL);
	s = ft_ary_get(&(t->fds), t->fds.item_count++);
	s->fd = fd;
	s->nl_off = -1;
	s->chars = ft_ary_create(sizeof(char));
	if (!s->chars.ptr)
		return (NULL);
	return (s);
}

static void		gnl_destroy(t_gnlstate *t, const int fd)
{
	size_t		i;
	t_gnl_fd	*s;

	i = -1ULL;
	s = NULL;
	while (++i < t->fds.item_count)
		if ((s = (t_gnl_fd*)ft_ary_get(&(t->fds), i))->fd == fd)
			break ;
	if (s == NULL)
	{
		return ;
	}
	ft_ary_destroy(&(s->chars));
	s->fd = 0;
	s->nl_off = -1;
	ft_ary_remove(&(t->fds), i);
}

ssize_t			gnl_read(t_gnl_fd *s)
{
	ssize_t read_ret;

	if (s->chars.item_cap < s->chars.item_count + BUFF_SIZE)
	{
		if (0 != ft_ary_grow(&s->chars, GROW_SIZE(s)))
			return (-1);
	}
	read_ret = read(s->fd, s->chars.item_count + (char*)s->chars.ptr,
			BUFF_SIZE);
	if (read_ret < 0)
		return (-1);
	if (read_ret == 0)
	{
		if (s->chars.item_count > 0)
		{
			s->nl_off = (ssize_t)s->chars.item_count;
			((char*)s->chars.ptr)[s->chars.item_count++] = 0;
			return (-2);
		}
		s->nl_off = -1;
		return (0);
	}
	s->chars.item_count += (size_t)read_ret;
	return (1);
}

static int		gnl_next(t_gnl_fd *s)
{
	char	*c;
	ssize_t	read_ret;

	if (0 != ft_ary_remove_mul(&s->chars, 0, (size_t)(s->nl_off + 1)))
		return (-1);
	while (1)
	{
		c = s->chars.ptr;
		while (c < ((char*)s->chars.ptr + s->chars.item_count) && *c != '\n')
			c++;
		if (c < ((char*)s->chars.ptr + s->chars.item_count) && *c == '\n')
		{
			s->nl_off = (c - (char*)s->chars.ptr);
			*c = 0;
			return (1);
		}
		read_ret = gnl_read(s);
		if (read_ret == -1 || read_ret == 0)
			return ((int)read_ret);
		if (read_ret == -2)
			return (1);
	}
}

t_gnlstate		g_bufio_state = {{0, sizeof(t_gnl_fd), 0, 1}};

int				get_next_line(const int fd, char **line)
{
	t_gnl_fd	*s;
	int			status;
	size_t		i;

	if (fd < 0 || !line)
		return (-1);
	i = -1ULL;
	s = NULL;
	while (++i < g_bufio_state.fds.item_count)
		if ((s = (t_gnl_fd*)ft_ary_get(&g_bufio_state.fds, i))->fd == fd)
			break ;
	if (s == NULL || s->fd != fd)
		if (!(s = gnl_setup(&g_bufio_state, fd)))
			return (-1);
	status = gnl_next(s);
	if (status == 1)
		*line = ft_strdup(s->chars.ptr);
	else
	{
		*line = 0;
		gnl_destroy(&g_bufio_state, fd);
	}
	return (status);
}
