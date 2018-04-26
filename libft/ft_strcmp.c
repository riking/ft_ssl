/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 10:08:57 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 11:25:08 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *o_s1, const char *o_s2)
{
	unsigned const char	*s1;
	unsigned const char	*s2;
	size_t				i;

	s1 = (unsigned const char*)o_s1;
	s2 = (unsigned const char*)o_s2;
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
