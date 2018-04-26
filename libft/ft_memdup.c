/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 10:52:02 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 10:57:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memdup(const void *mem, size_t size)
{
	void	*dst;

	dst = (void*)malloc(size);
	if (!dst)
		return (0);
	ft_memcpy(dst, mem, size);
	return (dst);
}
