/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ary_poplast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 12:50:23 by kyork             #+#    #+#             */
/*   Updated: 2016/11/28 12:52:37 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ary_poplast(t_array *ary)
{
	if (ary->item_cap == 0)
		return (FT_ARY_ERR_ISVIEW);
	if (ary->item_count > 0)
	{
		ary->item_count -= 1;
	}
	return (FT_ARY_ERR_OKAY);
}
