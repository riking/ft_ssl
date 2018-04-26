/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:23:44 by kyork             #+#    #+#             */
/*   Updated: 2017/01/25 17:31:57 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_private.h"
#include <ft_printf.h>
#include <stdlib.h>

#define NOINLINEVOID void __attribute__((noinline))

NOINLINEVOID	arena_error_break(void)
{
	__builtin_trap();
}

void			arena_badop(t_arena *a, char *msg)
{
	ft_dprintf(2, "*** Allocation error in arena %p\n", a);
	ft_dprintf(2, "*** %s\n", msg);
	ft_dprintf(2, "*** Set breakpoint in arena_error_break to debug\n");
	arena_error_break();
}

void			arena_badfree(t_arena *a, void *ptr, char *msg)
{
	ft_dprintf(2, "*** Allocation error in arena %p\n", a);
	ft_dprintf(2, "*** Memory at %p %s", ptr, msg);
	ft_dprintf(2, "*** Set breakpoint in arena_error_break to debug\n");
	arena_error_break();
}
