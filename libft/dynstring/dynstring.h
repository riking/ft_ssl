/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstring.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 22:25:04 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 22:32:24 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNSTRING_H
# define DYNSTRING_H

# include <sys/types.h>

typedef struct	s_dynstring {
	size_t	len;
	size_t	cap;
	char	*str;
}				t_dynstring;

t_dynstring		dynstring_new(const char *str);
int				dynstring_grow(t_dynstring *s, size_t min_size);
int				dynstring_appch(t_dynstring *s, char ch);
int				dynstring_appstr(t_dynstring *s, char *appendstr);
char			*dynstring_strdup(t_dynstring *s);
void			dynstring_destroy(t_dynstring *s);

#endif
