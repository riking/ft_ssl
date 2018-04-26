/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 19:32:15 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 10:57:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*ret;
	char	*fill;
	size_t	i;

	ret = (void*)malloc(size);
	if (!ret)
		return (0);
	fill = ret;
	i = 0;
	while (i < size)
	{
		*fill++ = 0;
		i++;
	}
	return (ret);
}
