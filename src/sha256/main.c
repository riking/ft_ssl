/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:13:30 by kyork             #+#    #+#             */
/*   Updated: 2018/05/04 17:07:48 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include <ft_printf.h>
#include <unistd.h>

int				ft_ssl_sha256(int argc, char **argv)
{
	t_sha256state	ctx;
	ssize_t			read_len;
	t_u8			buf[128];
	t_u8			digest[SHA256_OUTPUT_SIZE];

	ctx = sha256_init();
	while (1)
	{
		read_len = read(0, buf, 128);
		if (read_len < 0)
			ft_perrorf("read stdin");
		if (read_len <= 0)
			break ;
		sha256_write(&ctx, buf, read_len);
	}
	if (read_len < 0)
		return (1);
	sha256_finish(&ctx, digest);
	ft_printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
			"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
			"%02x\n", digest[0], digest[1], digest[2], digest[3], digest[4],
			digest[5], digest[6], digest[7], digest[8], digest[9], digest[10],
			digest[11], digest[12], digest[13], digest[14], digest[15],
			digest[16], digest[17], digest[18], digest[19], digest[20],
			digest[21], digest[22], digest[23], digest[24], digest[25],
			digest[26], digest[27], digest[28], digest[29], digest[30],
			digest[31]);
	return (0);
}

#ifdef SHA256_MAIN

int				main(int argc, char **argv)
{
	return (ft_ssl_sha256(argc, argv));
}
#endif
