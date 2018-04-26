/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:36:51 by kyork             #+#    #+#             */
/*   Updated: 2016/09/22 15:42:28 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	const char *s;

	s = str;
	while (*s)
	{
		if (((unsigned char)*s) == c)
			return ((char*)s);
		s++;
	}
	if (c == 0)
		return ((char*)s);
	return (0);
}
