/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_guard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:46:20 by kyork             #+#    #+#             */
/*   Updated: 2016/11/27 23:44:38 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GUARD_H
# define FT_GUARD_H

# define GFAIL(val, expr) {(void)(expr); return (val);}
# define GCONT(expr) {(void)(expr); continue;}
# define ASGUARD(f,v, ...) ({int _r=ft_asprintf(v,__VA_ARGS__);if (_r<0){ f }})
# define ZGUARD(fail, expr) if ((expr) != 0) { fail }
# define NGUARD(fail, expr) if ((expr) == NULL) { fail }
# define TGUARD(fail, expr) if ((expr)) { fail }

#endif
