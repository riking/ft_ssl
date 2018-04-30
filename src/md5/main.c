/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 13:13:30 by kyork             #+#    #+#             */
/*   Updated: 2018/04/30 13:24:31 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <ft_printf.h>
#include <unistd.h>

int				ft_ssl_md5(int argc, char **argv)
{
	t_md5state		ctx;
	ssize_t			read_len;
	t_u8			buf[128];
	t_u8			digest[MD5_OUTPUT_SIZE];

	ctx = md5_init();
	while (1)
	{
		read_len = read(0, buf, 128);
		if (read_len < 0)
			ft_perrorf("read stdin");
		if (read_len <= 0)
			break ;
		md5_write(&ctx, buf, read_len);
	}
	if (read_len < 0)
		return (1);
	md5_finish(&ctx, digest);
	ft_printf("%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
			"%02x", digest[0], digest[1], digest[2], digest[3], digest[4],
			digest[5], digest[6], digest[7], digest[8], digest[9], digest[10],
			digest[11], digest[12], digest[13], digest[14], digest[15]);
	return (0);
}

#ifdef MD5_MAIN

int				main(int argc, char **argv)
{
	return ft_ssl_md5(argc, argv);
}
#endif
