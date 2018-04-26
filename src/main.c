/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:55:56 by kyork             #+#    #+#             */
/*   Updated: 2018/04/25 18:26:54 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"
#include <libft.h>
#include <ft_printf.h>

static void	cmd_list(enum e_commandtype ty) {
	size_t	idx;

	idx = 0;
	while (g_command_list[idx].command_name)
	{
		if (g_command_list[idx].command_type == ty &&
				!g_command_list[idx].is_alias)
			ft_dprintf(2, "%s\n", g_command_list[idx].command_name);
		idx++;
	}
}

static void	usage(char *bad_cmd) {
	ft_dprintf(2, "%s: Error: '%s' is an invalid command.\n", ft_progname(),
			bad_cmd);
	ft_dprintf(2, "\nStandard commands:\n");
	cmd_list(CMD_OTHER);
	ft_dprintf(2, "\nMessage Digest commands:\n");
	cmd_list(CMD_HASH);
	ft_dprintf(2, "\nCipher commands:\n");
	cmd_list(CMD_CIPHER);
}

int			main(int argc, char **argv) {
	size_t			idx;

	ft_set_progname(argv[0]);
	if (argc == 0)
	{
		ft_dprintf(2, "usage: %s command [command opts] [command args]\n",
				ft_progname());
		exit(2);
	}
	idx = 0;
	while (g_command_list[idx].command_name)
	{
		if (0 == ft_strcmp(g_command_list[idx].command_name, argv[1]))
			return (g_command_list[idx].command_func(argc, argv));
		idx++;
	}
	usage(argv[1]);
	exit(2);
}
