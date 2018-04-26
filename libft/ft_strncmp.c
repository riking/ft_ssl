/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 10:08:57 by kyork             #+#    #+#             */
/*   Updated: 2016/09/21 16:02:17 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *o_s1, const char *o_s2, size_t n)
{
	unsigned const char	*s1;
	unsigned const char	*s2;
	size_t				i;

	s1 = (unsigned const char*)o_s1;
	s2 = (unsigned const char*)o_s2;
	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (n != 0 && i == n)
		return (s1[n - 1] - s2[n - 1]);
	else if (n == 0)
		return (0);
	return (s1[i] - s2[i]);
}
