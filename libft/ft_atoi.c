/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/11 12:41:31 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 16:21:33 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <limits.h>

static const char	*end_of_num(const char **str)
{
	const char *s;

	while (**str == '0')
		(*str)++;
	s = *str;
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			break ;
		s++;
	}
	return (s);
}

int					ft_atoi(const char *str)
{
	const char			*end;
	const char			*s;
	unsigned long long	result;
	int					sign;

	while (IS_SPACE(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}
	end = end_of_num(&str);
	result = 0;
	s = str - 1;
	while (++s < end)
		result = result * 10LL + (unsigned long long)(*s - '0');
	if (result > 2147483648LL || (sign == 1 && result == 2147483648LL)
			|| (end - str) > 19)
		errno = ERANGE;
	if ((end - str) > 19 || result >= 9223372036854775808uLL)
		return ((sign == 1) ? -1 : 0);
	return (sign * (int)result);
}
