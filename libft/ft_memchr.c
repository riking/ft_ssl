/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:06:24 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:25:43 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char *p;

	p = (unsigned const char*)s;
	while (n-- > 0)
	{
		if (*p == (unsigned char)c)
			return ((void*)p);
		p++;
	}
	return (NULL);
}
