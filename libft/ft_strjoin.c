/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:06:50 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 20:40:41 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*d;
	char	*dst;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_strnew(len);
	if (!dst)
		return (0);
	d = dst;
	while (*s1)
		*d++ = *s1++;
	while (*s2)
		*d++ = *s2++;
	*d = 0;
	return (dst);
}
