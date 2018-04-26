/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 10:46:39 by kyork             #+#    #+#             */
/*   Updated: 2016/09/24 21:13:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t cont_size)
{
	t_list	*n;
	void	*c;

	n = (t_list*)malloc(sizeof(t_list));
	if (!n)
		return (0);
	if (content)
	{
		c = ft_memdup(content, cont_size);
		if (!c)
		{
			free(n);
			return (0);
		}
		n->content = c;
		n->content_size = cont_size;
	}
	else
	{
		n->content = 0;
		n->content_size = 0;
	}
	n->next = 0;
	return (n);
}
