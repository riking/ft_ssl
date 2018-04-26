/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 09:16:29 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 20:15:15 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	const char *s;
	const char *f;
	const char *s_end;

	if (!*to_find)
		return ((char*)str);
	s_end = str + len;
	while (*str && str <= s_end)
	{
		s = str;
		f = to_find;
		while (*s && s < s_end && *f)
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
