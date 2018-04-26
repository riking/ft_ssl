/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 14:54:39 by kyork             #+#    #+#             */
/*   Updated: 2016/10/11 09:50:24 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_ary_destroy2(t_array **pary)
{
	if (*pary)
	{
		if ((*pary)->item_cap == 0)
			;
		else
			free((*pary)->ptr);
	}
	free(*pary);
	*pary = NULL;
}
