/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstring_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 22:37:24 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 22:38:39 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynstring.h"
#include <libft.h>
#include <stdlib.h>

char	*dynstring_strdup(t_dynstring *s)
{
	char	*str;

	str = (char*)malloc(s->len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s->str, s->len);
	str[s->len] = 0;
	return (str);
}
