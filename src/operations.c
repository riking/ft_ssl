/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:56:23 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:04:16 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

#include "md5/md5.h"
#include "sha256/sha256.h"

const t_mainopinfo		g_command_list[] = {
	{"md5", CMD_HASH, ft_ssl_md5, false},
	{"sha256", CMD_HASH, ft_ssl_sha256, false},
};
