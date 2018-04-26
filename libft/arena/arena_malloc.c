/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:34:33 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:45:24 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_private.h"

static inline void	*adj_ptr(void *ptr, size_t offset)
{
	char	*mem;

	mem = ptr;
	return (mem + offset);
}
