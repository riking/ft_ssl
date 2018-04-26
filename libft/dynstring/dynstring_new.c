/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstring_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 22:28:23 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 22:30:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynstring.h"
#include <libft.h>

t_dynstring	dynstring_new(const char *str)
{
	t_dynstring	s;

	s.len = ft_strlen(str);
	s.cap = s.len + 1;
	if (s.cap < 4)
		s.cap = 4;
	s.str = ft_memalloc(s.cap);
	if (!s.str)
		return (s);
	ft_memcpy(s.str, str, s.len + 1);
	return (s);
}
