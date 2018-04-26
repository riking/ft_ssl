/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 11:06:31 by kyork             #+#    #+#             */
/*   Updated: 2016/09/23 11:44:33 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** ft_lstpop is like ft_lstdelone, but it assigns the new list value, as
** opposed to null, into *alst
*/

void		ft_lstpop(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;

	node = *alst;
	*alst = node->next;
	del(node->content, node->content_size);
	free(node);
}
