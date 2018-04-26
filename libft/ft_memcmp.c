/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 10:08:57 by kyork             #+#    #+#             */
/*   Updated: 2016/09/21 16:06:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *o_s1, const void *o_s2, size_t n)
{
	unsigned const char	*s1;
	unsigned const char	*s2;
	size_t				i;

	s1 = (unsigned const char*)o_s1;
	s2 = (unsigned const char*)o_s2;
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
