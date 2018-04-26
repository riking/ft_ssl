/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 22:12:26 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:19:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_neg(int nbr, char **rp)
{
	if (nbr < 0)
	{
		*(*rp)++ = '-';
		if (nbr == -2147483648)
		{
			*(*rp)++ = '2';
			nbr %= 1000000000;
		}
		return (-nbr);
	}
	return (nbr);
}

char		*ft_itoa(int nbr)
{
	int		power_of_ten;
	char	*r;
	char	*rp;

	r = ft_strnew(11);
	if (!r)
		return (0);
	rp = r;
	nbr = handle_neg(nbr, &rp);
	power_of_ten = 1000000000;
	while (power_of_ten > nbr && power_of_ten > 1)
		power_of_ten /= 10;
	while (power_of_ten > 1)
	{
		*rp++ = ('0' + (char)(nbr / power_of_ten));
		nbr = nbr % power_of_ten;
		power_of_ten /= 10;
	}
	*rp++ = ('0' + (char)(nbr / power_of_ten));
	return (r);
}
