/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:39:16 by kyork             #+#    #+#             */
/*   Updated: 2016/11/10 13:40:16 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_basename(char *path)
{
	char *slash;
	char *p;

	slash = 0;
	p = path;
	while (*p)
	{
		if (*p == '/')
		{
			slash = p;
		}
		p++;
	}
	if (slash)
		return (slash + 1);
	else
		return (path);
}
