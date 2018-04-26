/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 09:16:29 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 20:14:59 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	const char *s;
	const char *f;

	if (!*to_find)
		return ((char*)str);
	while (*str)
	{
		s = str;
		f = to_find;
		while (*s && *f)
			if (*s++ != *f)
				break ;
			else
				f++;
		if (*f == 0)
			return ((char*)str);
		str++;
	}
	return (0);
}
