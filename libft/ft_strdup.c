/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:15:37 by kyork             #+#    #+#             */
/*   Updated: 2016/09/24 17:42:36 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dst;
	char	*d;

	len = ft_strlen(s1);
	dst = ft_strnew(len);
	if (!dst)
		return (0);
	d = dst;
	while (*s1)
		*d++ = *s1++;
	*d = 0;
	return (dst);
}
