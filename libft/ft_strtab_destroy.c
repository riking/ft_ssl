/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:48:36 by kyork             #+#    #+#             */
/*   Updated: 2017/01/12 15:49:34 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

void	ft_strtab_destroy(char **tab)
{
	int		idx;

	idx = 0;
	while (tab[idx])
	{
		free(tab[idx++]);
	}
	free(tab);
}
