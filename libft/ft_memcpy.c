/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:29:10 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:22:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t length)
{
	size_t		t;
	char		*d;
	const char	*s;

	if (length == 0)
		return (dst);
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
	return (dst);
}
