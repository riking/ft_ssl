/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:37:39 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 14:45:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmain.h"
#include "../hmac/hmac.h"

#include <libft.h>
#include <ft_printf.h>

void			hashmain_setup_hmac(t_flags *flags)
{
	t_ft_hash	hmac;

	if (!flags->hmac_key)
		return ;
	hmac = hmac_create(flags->alg, flags->hmac_key, ft_strlen(flags->hmac_key));
	flags->alg.vtable->free(flags->alg.state);
	flags->alg = hmac;
}
