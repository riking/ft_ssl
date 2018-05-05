/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:56:23 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 20:13:44 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

#include "md5/md5.h"
#include "sha256/sha256.h"

const t_mainopinfo		g_command_list[] = {
	{"md5", CMD_HASH, ft_ssl_hashmain, false},
	{"sha256", CMD_HASH, ft_ssl_hashmain, false},
};

const t_ft_hash_name	g_hash_list[] = {
	{&g_md5_hash_vtable, "md5", "MD5"},
	{&g_sha256_hash_vtable, "sha256", "SHA256"},
};
