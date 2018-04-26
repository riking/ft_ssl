/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 22:12:26 by kyork             #+#    #+#             */
/*   Updated: 2016/10/04 22:19:11 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	int power_of_ten;

	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		if (nbr == -2147483648)
		{
			ft_putchar_fd('2', fd);
			nbr %= 1000000000;
		}
		nbr = -nbr;
	}
	power_of_ten = 1000000000;
	while (power_of_ten > nbr && power_of_ten > 1)
		power_of_ten /= 10;
	while (power_of_ten > 1)
	{
		ft_putchar_fd('0' + (char)(nbr / power_of_ten), fd);
		nbr = nbr % power_of_ten;
		power_of_ten /= 10;
	}
	ft_putchar_fd('0' + (char)(nbr / power_of_ten), fd);
}
