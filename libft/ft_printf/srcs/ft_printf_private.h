/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:34:05 by kyork             #+#    #+#             */
/*   Updated: 2016/11/10 20:48:28 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PRIVATE_H
# define FT_PRINTF_PRIVATE_H

# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <sys/types.h>

# include <ft_printf.h>

# define MAX(a, b) ((a) < (b) ? (b) : (a))
# define ARRAYLEN(ary) ((ssize_t)(sizeof(ary) / sizeof(*ary)))

# define FD_BUF_SIZE 128

typedef struct		s_printer_data_fd
{
	int				fd;
	char			*buf;
	size_t			used_buf;
}					t_printer_data_fd;

typedef struct		s_printer_data_str
{
	char			*str;
}					t_printer_data_str;

typedef struct		s_printer_data_noop
{
	char			bogus;
}					t_printer_data_noop;

typedef union		u_printer_data
{
	t_printer_data_fd	fd;
	t_printer_data_str	str;
	t_printer_data_noop	noop;
}					t_printer_data;

typedef enum		e_printf_lenmod {
	PF_SIZE_NONE,
	PF_SIZE_HH,
	PF_SIZE_H,
	PF_SIZE_L,
	PF_SIZE_LL,
	PF_SIZE_J,
	PF_SIZE_Z,
	PF_SIZE_LD,
}					t_printf_lenmod;

# define PF_FLAG_ZERO_PAD      (1 << 0)
# define PF_FLAG_ALTERNATE     (1 << 1)
# define PF_FLAG_ALIGN_LEFT    (1 << 2)
# define PF_FLAG_SIGN_ALWAYS   (1 << 3)
# define PF_FLAG_SIGN_PLUS     (1 << 4)
# define PF_FLAG_THOUS_SEP     (1 << 5)
# define PF_FLAG_HAVE_PRECIS   (1 << 6)
# define PF_FLAG_PREC_DO_ZERO  (1 << 7)
# define PF_FLAG_SSE_SEP_COMMA ((1 << 8) | (0 << 9) | (0 << 10))
# define PF_FLAG_SSE_SEP_SEMI  ((1 << 8) | (1 << 9) | (0 << 10))
# define PF_FLAG_SSE_SEP_COLON ((1 << 8) | (0 << 9) | (1 << 10))
# define PF_FLAG_SSE_SEP_UNDER ((1 << 8) | (1 << 9) | (1 << 10))

# define HAVE_FLAG(parse, flag) (0 != ((parse)->flags & (flag)))

/*
** notes:
**
** used_size will never be more than 1 less than max_print
** It ends up used to place the null in snprintf() etc
*/

typedef struct		s_printf_parse {
	int				(*printer)(struct s_printf_parse *flags, char c);
	size_t			max_print;
	t_printer_data	print_data;

	size_t			used_size;

	int				(*func)(struct s_printf_parse *flags, va_list args);
	unsigned int	min_width;
	unsigned int	precis;
	uint16_t		flags;
	t_printf_lenmod lenmod;
	char			spec;

	char			sign;
	char			ox;
}					t_printf_parse;

typedef	int			(*t_printf_func)(
						t_printf_parse *flags,
						va_list args);

typedef	int			(*t_printer)(
						t_printf_parse *flags,
						char c);

typedef struct		s_specifiers {
	t_printf_func	func;
	char			chr;
	bool			flag_l;
}					t_specifiers;

typedef enum		e_doubleflag {
	DOUBLEFLAG_NONE,
	DOUBLEFLAG_CAN,
	DOUBLEFLAG_DID,
}					t_doubleflag;

typedef struct		s_modifiers {
	t_printf_lenmod flag;
	size_t			bytes;
	char			chr;
	t_doubleflag	doubled;
}					t_modifiers;

typedef struct		s_fmtflags {
	uint16_t		mask;
	char			chr;
}					t_fmtflags;

# ifdef FT_PRINTF_COUNT_ERR
#  define COUNT(r, val) ({ssize_t _t=(val);if(_t == -1)return(-1);(r)+=_t;})
#  define COUNTX(r,x,v) ({ssize_t _t=(v);if(_t==-1){x;return(-1);}(r)+=_t;})
# endif

/*
** returns the number of characters in the format string
*/

ssize_t				ft_printf_parse(
						const char *fmtptr,
						t_printf_parse *flags,
						va_list args);

void				ft_printf_setup_parse(
						t_printf_parse *parse,
						t_printer printer,
						size_t max_print);

void				ft_printf_reset_parse(t_printf_parse *parse);

void				ft_printf_numflag(
						const char **fmt,
						t_printf_parse *parse,
						va_list args);

ssize_t				ft_do_printf(
						const char *fmt,
						va_list args,
						t_printf_parse *parse);

ssize_t				ft_printf_strichr(const char *str, char c);

uint64_t			ft_printf_get_int_arg(
						t_printf_parse *parse,
						bool sign,
						va_list args);

int					ft_printf_printer_fd(t_printf_parse *flags, char c);
int					ft_printf_printer_str(t_printf_parse *flags, char c);
int					ft_printf_printer_noop(t_printf_parse *flags, char c);

int					ft_printf_digout(
						t_printf_parse *flags,
						char *str,
						size_t strlen);

int					ft_printf_strout(
						t_printf_parse *flags,
						char *str,
						size_t strlen);

int					ft_printf_d(t_printf_parse *flags, va_list args);
int					ft_printf_u(t_printf_parse *flags, va_list args);
int					ft_printf_o(t_printf_parse *flags, va_list args);
int					ft_printf_x(t_printf_parse *flags, va_list args);
int					ft_printf_c(t_printf_parse *flags, va_list args);
int					ft_printf_s(t_printf_parse *flags, va_list args);

int					ft_printf_percent(t_printf_parse *flags, va_list args);

#endif
