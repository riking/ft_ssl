/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:21:39 by kyork             #+#    #+#             */
/*   Updated: 2018/05/06 15:06:29 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmain.h"

#include <ft_printf.h>
#include <ft_guard.h>

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*
** ft_guard body for do_hash
** Tricky to free the t_ft_hash and print the error and return, so ft_guard
*/
#define GUARDF1(fn) ft_perrorf("%s: %s: %s", ft_progname(), flags->name, fn)
#define GUARDF2 h.vtable->free(h.state)
#define GUARDFAIL {GUARDF1(op->filename); GUARDF2; return (1);}

static char		*hexprint_digest(t_flags *flags, t_u8 *digest)
{
	size_t	outsz;
	char	*digest_str;
	size_t	idx;

	outsz = flags->alg.vtable->output_size;
	digest_str = malloc(outsz * 3 + 1);
	idx = 0;
	while (idx < outsz)
	{
		ft_snprintf(digest_str + (idx * (flags->with_colons ? 3 : 2)), 4,
				(flags->with_colons ? "%02x:" : "%02x"), digest[idx]);
		idx++;
	}
	if (flags->with_colons && outsz > 0)
		digest_str[outsz * 3 - 1] = 0;
	return (digest_str);
}

static int		output_hash(t_flags *flags, t_ft_hash *h,
					t_hashmain_outfmt fmt, t_hashop *op)
{
	t_u8	*digest;
	char	*digest_str;

	digest = malloc(h->vtable->output_size);
	h->vtable->finish(h->state, digest);
	digest_str = hexprint_digest(flags, digest);
	if (fmt == HASHMAIN_FMT_RICH && op && op->is_string)
		ft_printf("%s (\"%s\") = %s\n", flags->name_rich, op->filename,
				digest_str);
	else if (fmt == HASHMAIN_FMT_RICH && op)
		ft_printf("%s (%s) = %s\n", flags->name_rich, op->filename, digest_str);
	else if (fmt == HASHMAIN_FMT_COREUTILS && op && op->is_string)
		ft_printf("%s \"%s\"\n", digest_str, op->filename);
	else if (fmt == HASHMAIN_FMT_COREUTILS && op)
		ft_printf("%s %s\n", digest_str, op->filename);
	else
		ft_printf("%s\n", digest_str);
	free(digest_str);
	free(digest);
	return (0);
}

/*
** cast of op->filename is const-safe, write() does not modify its argument
*/

int				hashmain_do_hash(t_flags *flags, t_hashop *op)
{
	t_ft_hash	h;
	int			fd;

	h.vtable = flags->alg.vtable;
	h.state = h.vtable->init(flags->alg.state);
	if (op->is_string)
		h.vtable->write(h.state, (t_u8*)op->filename, ft_strlen(op->filename));
	else
	{
		fd = open(op->filename, O_RDONLY);
		TGUARD(GUARDFAIL, fd < 0);
		TGUARD(GUARDFAIL, (hashmain_hash_fd(flags, &h, fd, false) < 0));
	}
	output_hash(flags, &h, flags->outfmt, op);
	h.vtable->free(h.state);
	return (0);
}

int				hashmain_hash_fd(t_flags *flags, t_ft_hash *h,
									int fd, bool tee_stdout)
{
	ssize_t		read_ret;
	t_u8		buf[1024];

	while (1)
	{
		read_ret = read(fd, buf, 1024);
		if (read_ret < 0)
			return (1);
		if (read_ret == 0)
			break ;
		h->vtable->write(h->state, buf, (size_t)read_ret);
		if (tee_stdout)
			if (write(1, buf, read_ret) < 0)
			{
				ft_perrorf("%s: %s: write stdout", ft_progname(), flags->name);
				errno = 0;
				return (1);
			}
	}
	return (0);
}

int				hashmain_run(t_flags *flags)
{
	t_ft_hash	h;
	int			any_err;
	size_t		idx;

	any_err = 0;
	if (flags->stdin_copy || flags->ops.item_count == 0)
	{
		h.vtable = flags->alg.vtable;
		h.state = h.vtable->init(flags->alg.state);
		if (hashmain_hash_fd(flags, &h, 0, flags->stdin_copy) < 0)
			any_err |= 1;
		else
			any_err |= output_hash(flags, &h, HASHMAIN_FMT_PLAIN, NULL);
		h.vtable->free(h.state);
	}
	idx = 0;
	while (idx < flags->ops.item_count)
	{
		any_err |= hashmain_do_hash(flags,
				(t_hashop*)ft_ary_get(&flags->ops, idx));
		idx++;
	}
	return (any_err != 0);
}
