/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 13:29:23 by kyork             #+#    #+#             */
/*   Updated: 2016/11/10 12:24:16 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#define IS_SEP(x) (x == ' ' || x == '\n' || x == '\t')

static void	getbounds(const char **pstr, size_t *plen)
{
	const char	*str;
	ssize_t		len;

	str = *pstr;
	while (str[0] && IS_SEP(str[0]))
		str++;
	*pstr = str;
	len = (ft_strlen(str));
	while (len > 0)
	{
		len--;
		if (!IS_SEP(str[len]))
		{
			*plen = len + 1;
			return ;
		}
	}
	*plen = len;
}

char		*ft_strtrim(const char *str)
{
	size_t	len;
	size_t	i;
	char	*dest;

	if (!str)
		return (0);
	getbounds(&str, &len);
	dest = ft_strnew(len);
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
