/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:56:26 by kyork             #+#    #+#             */
/*   Updated: 2018/04/25 18:28:25 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPERATIONS_H
# define FT_SSL_OPERATIONS_H

# include <stdbool.h>

typedef int					(*t_commandfunc)(int argc, char** argv);

enum						e_commandtype {
	CMD_OTHER,
	CMD_HASH,
	CMD_CIPHER,
};

typedef struct				s_mainopinfo {
	const char *		command_name;
	enum e_commandtype	command_type;
	t_commandfunc		command_func;
	bool				is_alias;
}							t_mainopinfo;

extern const t_mainopinfo	g_command_list[];

#endif
