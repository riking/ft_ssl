/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 12:58:03 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:26:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return value is length of dst plus length of src, BUT
**   if dst is longer than size, we use that as dst's length
**     and don't copy anything (*1)
** The "space left" is the size parameter minus length of dst
** If there's no space left, don't copy anything (*1)
** While there's at least 1 character of space left, copy
** Keep counting the length of src
** Place the null character at the end
** return dst length + src length
*/

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		dstsize;
	size_t		space_left;
	char		*d;
	const char	*s;

	d = dst;
	space_left = size;
	while (space_left-- != 0 && *d)
		d++;
	dstsize = (size_t)(d - dst);
	space_left = size - dstsize;
	if (space_left <= 0)
		return (size + ft_strlen(src));
	s = src;
	while (*s && space_left-- > 1)
		*d++ = *s++;
	while (*s)
		s++;
	*d = 0;
	return (dstsize + (size_t)(s - src));
}
