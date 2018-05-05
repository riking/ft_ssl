/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:37:39 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:40:42 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmain.h"

#include <libft.h>
#include <ft_printf.h>

void			hashmain_setup_hmac(t_flags *flags)
{
	if (!flags->hmac_key)
		return ;
	ft_dprintf(2, "%s: hash: hmac not implemented\n", ft_progname());
}
