/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 12:19:51 by kyork             #+#    #+#             */
/*   Updated: 2016/09/21 16:45:03 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t nb)
{
	char	*orig_dst;
	size_t	i;

	orig_dst = dst;
	while (*dst)
		dst++;
	i = 0;
	while (*src && i++ < nb)
	{
		*dst++ = *src++;
	}
	*dst = 0;
	return (orig_dst);
}
