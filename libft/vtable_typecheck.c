/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtable_typecheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:33:23 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:35:27 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ft_printf.h>
#include <stdlib.h>

void		vtable_typecheck(const char *source,
					const void *actual, const void *expectvt)
{
	if (actual == expectvt)
		return ;
	ft_dprintf(2, "[libft] bad vtable call to a function of type %s\n"
			"[libft] actual vtable: %p\n"
			"[libft] expected vtable: %p\n", source, actual, expectvt);
	abort();
}
