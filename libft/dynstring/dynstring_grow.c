/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstring_grow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 22:40:32 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 23:08:50 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynstring.h"
#include <stdlib.h>
#include <libft.h>

int			dynstring_grow(t_dynstring *s, size_t min_size)
{
	size_t	new_size;
	char	*m;

	if (s->cap > min_size + 1)
		return (0);
	new_size = s->cap * 2;
	if (new_size < min_size)
		new_size = min_size;
	if (new_size < 4)
		new_size = 4;
	m = malloc(new_size);
	if (!m)
		return (-1);
	ft_memcpy(m, s->str, s->len);
	ft_bzero(m + s->len, new_size - s->len);
	free(s->str);
	s->str = m;
	s->cap = new_size;
	return (0);
}
