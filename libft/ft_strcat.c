/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 12:19:51 by kyork             #+#    #+#             */
/*   Updated: 2016/09/21 16:40:40 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	char *orig_dst;

	orig_dst = dst;
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return (orig_dst);
}
