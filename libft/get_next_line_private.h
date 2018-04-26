/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:34:19 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 14:38:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_PRIVATE_H
# define GET_NEXT_LINE_PRIVATE_H

# include <libft.h>
# include <sys/types.h>

typedef struct		s_gnl_fd {
	int		fd;
	ssize_t	nl_off;
	t_array	chars;
}					t_gnl_fd;

typedef struct		s_gnlstate {
	t_array fds;
}					t_gnlstate;

# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
# endif

extern t_gnlstate	g_bufio_state;

int					get_next_line(const int fd, char **line);
int					get_next_char(const int fd);

t_gnl_fd			*gnl_setup(t_gnlstate *t, const int fd);
ssize_t				gnl_read(t_gnl_fd *s);

#endif
