/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 11:01:11 by kyork             #+#    #+#             */
/*   Updated: 2018/05/09 17:33:30 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <sys/types.h>

# ifdef HAVE_ALLOCWRAP
#  include <ft_alloc_wrap.h>
# endif

# define ARRAYLEN(a) ((ssize_t)(sizeof(a) / sizeof(*a)))
# define MAX(a, b) ({typeof(a)_a=(a);typeof(b)_b=(b);(_a<_b)?_b:_a;})

void				ft_putchar(char c);
void				ft_putchar_uni(int cp);
void				ft_putstr(char const *str);
void				ft_putendl(char const *str);
void				ft_putnbr(int nbr);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar_uni_fd(int cp, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

char				*ft_itoa(int n);
int					ft_atoi(const char *str);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_strtab_destroy(char **tab);

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *restrict src,
						int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big,
						const char *little, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

char				*ft_basename(char *path);

void				ft_set_progname(char *argv0);
const char			*ft_progname(void);

# ifndef IS_SPACE
#  define IS_SPACE(x) (x==' '||x=='\n'||x=='\t'||x=='\r'||x=='\v'||x=='\f')
# endif

# ifndef UNUSED
#  define UNUSED(x) (void)(x)
# endif

# define FD_STDIN  0
# define FD_STDOUT 1
# define FD_STDERR 2

/*
** Linked list
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Growing Array
**
** t_array is an autogrowing array implementation. The size of an element
** is provided when the array is constructed, and used in every function.
**
** ft_ary_create() allocates a t_array structure with the given size. destroy()
** must be called to free the memory.
**
** set(), append(), and insert() perform a memory copy to insert the item.
**
** Any references into the array's ptr are stale after a call to grow(),
** insert(), append(), or clear().
**
** Functions returning int return one of the FT_ARY_ERR_* constants.
** Functions returning void do not fail.
** The get() function performs no bounds checking - don't pass invalid indices.
**
** If item_cap is 0, the array is a view of other memory and cannot be grown.
** Functions changing the size will fail (grow, append, remove).
*/

# ifdef __APPLE__
#  define CONSTSIZET const size_t
# else
#  define CONSTSIZET size_t
# endif

typedef struct		s_array
{
	void			*ptr;
	CONSTSIZET		item_size;
	size_t			item_count;
	size_t			item_cap;
}					t_array;

# define FT_ARY_NULL ((t_array){0, 0, 0, 0})
# define FT_ARY_DEFAULT_CAP 4
# define FT_ARY_GROW_FACTOR 2
# define FT_ARY_ERR_OKAY 0
# define FT_ARY_ERR_ALLOC -1
# define FT_ARY_ERR_ISVIEW -2
# define FT_ARY_ERR_BOUNDS -3

t_array				ft_ary_create(const size_t sizeof_item);
t_array				ft_ary_clone(t_array ary, size_t min_size);
t_array				ft_ary_viewof(void *ptr, size_t count,
						const size_t sizeof_item);
void				*ft_ary_get(t_array *ary, size_t idx);
int					ft_ary_set(t_array *ary, void *item, size_t idx);
int					ft_ary_grow(t_array *ary, size_t min_item_cap);
int					ft_ary_append(t_array *ary, void *item);
int					ft_ary_insert(t_array *ary, void *item, size_t idx);
int					ft_ary_poplast(t_array *ary);
int					ft_ary_remove(t_array *ary, size_t idx);
int					ft_ary_remove_mul(t_array *ary, size_t idx, size_t count);
int					ft_ary_clear(t_array *ary);
void				ft_ary_foreach(t_array *ary, void (*func)(void*, size_t));
void				ft_ary_destroy(t_array *ary);
void				ft_ary_destroy2(t_array **pary);
void				ft_ary_swap(t_array *ary, size_t i, size_t j);

typedef int			(*t_sortfunc)(void *left, void *right, size_t size,
						void *data);
void				ft_ary_sort(t_array *ary, t_sortfunc cmp, void *cmp_data);

/*
** Reader/Writer vtable functions
*/

void				vtable_typecheck(const char *source,
						const void *actual, const void *expectvt);

typedef struct		s_ft_reader_vtable {
	ssize_t		(*read)(void *state, char *buf, size_t len);
	void		(*free)(void *state);
}					t_ft_reader_vtable;
typedef struct		s_ft_writer_vtable {
	ssize_t		(*write)(void *state, const char *buf, size_t len);
	void		(*free)(void *state);
}					t_ft_writer_vtable;

typedef struct		s_ft_reader {
	const t_ft_reader_vtable	*vtable;
	void						*state;
}					t_ft_reader;
typedef struct		s_ft_writer {
	const t_ft_writer_vtable	*vtable;
	void						*state;
}					t_ft_writer;

t_ft_reader			ft_reader_fd(int fd);

t_ft_reader			ft_reader_str(const char *str, size_t len);
size_t				ft_strreader_count(t_ft_reader obj);

t_ft_reader			ft_reader_null(void);

t_ft_writer			ft_writer_fd(int fd);

t_ft_writer			ft_writer_str(char *buf, size_t buf_len);
size_t				ft_strwriter_count(t_ft_writer obj);

t_ft_writer			ft_writer_null(void);

/*
** ft_autostrwriter -- build up an in-memory string via writes
** ft_autostrwriter_release -- Release control of the allocated string so it is
** not destroyed when the writer is freed.  Further operations on the writer
** except freeing are invalid.
*/

t_ft_writer			ft_autostrwriter(char **str);
char				*ft_autostrwriter_get(t_ft_writer obj);
void				ft_autostrwriter_release(t_ft_writer obj);
size_t				ft_autostrwriter_count(t_ft_writer obj);

/*
** Extra functions
*/

void				*ft_memdup(const void *content, size_t size);
void				ft_lstpop(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_arytolst(const void *start, size_t content_size,
						size_t count);

int					get_next_line(const int fd, char **line);

/*
** gnc returns -1 on error and EOF.
** on EOF, errno will be set to 0. check errno to distinguish
*/
int					get_next_char(const int fd);

#endif
