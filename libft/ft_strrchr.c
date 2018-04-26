/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 15:36:51 by kyork             #+#    #+#             */
/*   Updated: 2016/09/22 15:43:32 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char *s;

	s = str;
	while (*s)
		s++;
	if (c == 0)
		return ((char*)s);
	while (s > str)
	{
		s--;
		if (((unsigned char)*s) == c)
			return ((char*)s);
	}
	return (0);
}
