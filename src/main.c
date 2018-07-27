/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:55:56 by kyork             #+#    #+#             */
/*   Updated: 2018/05/22 14:13:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

#include <libft.h>
#include <ft_printf.h>

#include <stdlib.h>
#include <unistd.h>

static void	cmd_list(enum e_commandtype ty)
{
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

static void	usage(void)
{
	ft_dprintf(2, "\nStandard commands:\n");
	cmd_list(CMD_OTHER);
	ft_dprintf(2, "\nMessage Digest commands:\n");
	cmd_list(CMD_HASH);
	ft_dprintf(2, "\nCipher commands:\n");
	cmd_list(CMD_CIPHER);
}

static int	console(void)
{
	char	*line;
	int		status;
	char	**argv;
	int		idx;

	while (1)
	{
		ft_dprintf(0, "%s> ", ft_progname());
		status = get_next_line(0, &line);
		if (status != 1)
			break ;
		argv = ft_strsplit(line, ' ');
		idx = -1;
		while (argv[0] && g_command_list[++idx].command_name)
			if (0 == ft_strcmp(argv[0], g_command_list[idx].command_name))
				return (g_command_list[idx].command_func(1, argv));
		if (argv[0] && 0 == ft_strcmp(argv[0], "help"))
			usage();
		else if (argv[0])
			ft_dprintf(0, "unknown command '%s'\n", argv[0]);
		ft_strtab_destroy(argv);
	}
	return (2);
}

int			main(int argc, char **argv)
{
	size_t			idx;

	ft_set_progname(argv[0]);
	if (argc < 2)
		return (console());
	idx = 0;
	while (g_command_list[idx].command_name && argv[1])
	{
		if (0 == ft_strcmp(g_command_list[idx].command_name, argv[1]))
		{
			return (g_command_list[idx].command_func(argc - 1, argv + 1));
		}
		idx++;
	}
	ft_dprintf(2, "%s: Error: '%s' is an invalid command.\n", ft_progname(),
			argv[1]);
	usage();
	exit(2);
}
