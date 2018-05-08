/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:18:28 by kyork             #+#    #+#             */
/*   Updated: 2018/05/07 18:45:09 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WRITER_H
# define FT_WRITER_H

# include "../libft.h"

typedef struct					s_ft_strwriter_state {
	char		*buf;
	size_t		idx;
	size_t		cap;
}								t_ft_strwriter_state;

typedef struct					s_ft_autostrwriter_state {
	t_array		ary;
	char		**dst;
}								t_ft_autostrwriter_state;

extern const t_ft_writer_vtable	g_ft_fdwriter_vtable;
extern const t_ft_writer_vtable	g_ft_strwriter_vtable;
extern const t_ft_writer_vtable	g_ft_nullwriter_vtable;
extern const t_ft_writer_vtable	g_ft_autostrwriter_vtable;

#endif
