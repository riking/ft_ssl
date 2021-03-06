/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:56:23 by kyork             #+#    #+#             */
/*   Updated: 2018/07/27 12:39:47 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

#include "md5/md5.h"
#include "sha256/sha256.h"

const t_mainopinfo		g_command_list[] = {
	{"md5", CMD_HASH, ft_ssl_hashmain, false},
	{"sha256", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2b", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2b-512", CMD_HASH, ft_ssl_hashmain, true},
	{"blake2b-384", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2b-256", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2s", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2s-256", CMD_HASH, ft_ssl_hashmain, false},
	{"blake2s-128", CMD_HASH, ft_ssl_hashmain, false},
	{NULL, 0, NULL, false},
};

const t_ft_hash_name	g_hash_list[] = {
	{&g_md5_hash_vtable, "md5", "MD5"},
	{&g_sha256_hash_vtable, "sha256", "SHA256"},
	{&g_blake2b_512_hash_vtable, "blake2b", "BLAKE2b"},
	{&g_blake2b_512_hash_vtable, "blake2b-512", "BLAKE2b"},
	{&g_blake2b_384_hash_vtable, "blake2b-384", "BLAKE2b-384"},
	{&g_blake2b_256_hash_vtable, "blake2b-256", "BLAKE2b-256"},
	{&g_blake2s_256_hash_vtable, "blake2s", "BLAKE2s"},
	{&g_blake2s_256_hash_vtable, "blake2s-256", "BLAKE2s"},
	{&g_blake2s_128_hash_vtable, "blake2s-128", "BLAKE2s-128"},
	{NULL, NULL, NULL},
};
