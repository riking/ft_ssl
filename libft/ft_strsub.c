/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 16:19:45 by kyork             #+#    #+#             */
/*   Updated: 2016/09/24 17:51:09 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (0);
	dst = ft_strnew(len);
	if (!dst)
		return (0);
	ft_strncpy(dst, s + start, len);
	dst[len] = 0;
	return (dst);
}
