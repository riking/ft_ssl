/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:41:54 by kyork             #+#    #+#             */
/*   Updated: 2016/09/24 17:44:50 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*r;
	unsigned int	i;

	if (!f || !s)
		return (0);
	r = ft_strdup(s);
	if (!r)
		return (0);
	i = 0;
	while (s[i])
	{
		r[i] = f(s[i]);
		i++;
	}
	return (r);
}
