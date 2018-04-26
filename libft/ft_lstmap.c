/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 12:08:19 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 20:12:58 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstmap_del(void *content, size_t content_size)
{
	free(content);
	UNUSED(content_size);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*tail;
	t_list	*tmp;

	if (!lst)
		return (0);
	tail = 0;
	tmp = 0;
	while (lst)
	{
		tmp = ft_lstnew(lst->content, lst->content_size);
		if (!tmp)
			break ;
		tmp = f(tmp);
		if (tail)
			tail->next = tmp;
		else
			head = tmp;
		tail = tmp;
		lst = lst->next;
	}
	if (!tmp)
		ft_lstdel(&head, ft_lstmap_del);
	return (head);
}
