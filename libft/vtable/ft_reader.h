/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:55:38 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:16:51 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READER_H
# define FT_READER_H

# include "../libft.h"

typedef struct					s_ft_strreader_state {
	const char	*buf;
	size_t		idx;
	size_t		cap;
}								t_ft_strreader_state;

extern const t_ft_reader_vtable	g_ft_fdreader_vtable;
extern const t_ft_reader_vtable	g_ft_strreader_vtable;
extern const t_ft_reader_vtable	g_ft_nullreader_vtable;

#endif
