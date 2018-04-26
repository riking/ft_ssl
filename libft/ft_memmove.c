/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:29:10 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:22:05 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memmove_backwards(void *dst, const void *src, size_t length)
{
	size_t		t;
	char		*d;
	char const	*s;

	d = dst;
	s = src;
	s += length;
	d += length;
	t = length / 1;
	while (t > 0)
	{
		s -= 1;
		d -= 1;
		*d = *s;
		t--;
	}
}

static void	ft_memmove_forwards(void *dst, const void *src, size_t length)
{
	size_t		t;
	char		*d;
	char const	*s;

	d = dst;
	s = src;
	t = length / 1;
	while (t > 0)
	{
		*d = *s;
		s += 1;
		d += 1;
		t--;
	}
}

void		*ft_memmove(void *dst, const void *src, size_t length)
{
	if (src < dst)
		ft_memmove_backwards(dst, src, length);
	else
		ft_memmove_forwards(dst, src, length);
	return (dst);
}
