# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/22 09:02:39 by kyork             #+#    #+#              #
#    Updated: 2018/05/22 14:26:26 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PREFIX		= $(HOME)

FILENAMES	+= get_next_line.c get_next_char.c
FILENAMES	+= ft_progname.c ft_basename.c

FILENAMES	+= dynstring/dynstring_appch.c dynstring/dynstring_destroy.c
FILENAMES	+= dynstring/dynstring_grow.c dynstring/dynstring_new.c
FILENAMES	+= dynstring/dynstring_strdup.c

FILENAMES	+= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
FILENAMES	+= ft_toupper.c ft_tolower.c
TESTS		+= isstuff

FILENAMES	+= ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c
FILENAMES	+= ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
TESTS		+= putstuff
FILENAMES	+= ft_itoa.c
TESTS		+= putnbr

FILENAMES	+= ft_atoi.c
TESTS		+= atoi

FILENAMES	+= ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c ft_strlen.c
TESTS		+= strcpy strncpy			strcmp strncmp           strlen

FILENAMES	+= ft_strequ.c ft_strnequ.c
TESTS		+=

FILENAMES	+= ft_memmove.c ft_memcpy.c ft_memccpy.c ft_memcmp.c
TESTS		+= memmove memcpy memccpy memcmp

FILENAMES	+= ft_strstr.c ft_memchr.c ft_strchr.c ft_strrchr.c
FILENAMES	+= ft_strnstr.c
TESTS		+= strstr memchr           strchr

FILENAMES	+= ft_strcat.c ft_strncat.c ft_strlcat.c
TESTS		+= strcat strncat strlcat

FILENAMES	+= ft_strjoin.c
TESTS		+= strjoin

FILENAMES	+= ft_strsub.c
TESTS		+= strsub

FILENAMES	+= ft_strsplit.c ft_strtrim.c ft_strtab_destroy.c
TESTS		+= split strtrim

# need tests
FILENAMES	+= ft_memset.c ft_bzero.c ft_strnew.c ft_memalloc.c ft_strdup.c ft_memdel.c
FILENAMES	+= ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c

FILENAMES	+= ft_putchar_uni_fd.c
TESTS		+= unicode

TESTS		+= quentin yachaka

FILENAMES	+= ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c
FILENAMES	+= ft_lstiter.c ft_lstmap.c
TESTS		+= lstdel

FILENAMES	+= ft_lstpop.c ft_memdup.c

FILENAMES	+= ft_ary_create.c ft_ary_viewof.c ft_ary_set.c ft_ary_get.c
FILENAMES	+= ft_ary_grow.c ft_ary_append.c ft_ary_insert.c ft_ary_remove.c
FILENAMES	+= ft_ary_clear.c ft_ary_destroy.c ft_ary_swap.c ft_ary_sort.c
FILENAMES	+= ft_ary_remove_mul.c ft_ary_destroy2.c
FILENAMES	+= ft_ary_foreach.c ft_ary_clone.c ft_ary_poplast.c
TESTS		+= ary

FILENAMES	+= vtable_typecheck.c
FILENAMES	+= vtable/ft_reader_fd.c vtable/ft_reader_null.c vtable/ft_reader_str.c
FILENAMES	+= vtable/ft_writer_fd.c vtable/ft_writer_null.c vtable/ft_writer_str.c
FILENAMES	+= vtable/ft_writer_autostr.c vtable/ft_writer_autostr2.c

CC			= gcc

CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
LDFLAGS		+= -Wall -Wextra -Wmissing-prototypes
#CFLAGS		+= -Wall -Wextra -Wfloat-equal -Wundef -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors
#LDFLAGS		+= -Wall -Wextra -Wfloat-equal -Wundef -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors

CFLAGS		+= -Iincludes/

#ifndef NO_WERROR
	CFLAGS += -Werror
	LDFLAGS += -Werror
#endif

ifeq ($(DEBUG), 1)
	#CFLAGS	+= -fsanitize=address
	#LDFLAGS	+= -fsanitize=address
else
	#CFLAGS	+= -O3 -fomit-frame-pointer -DNDEBUG -flto
	#LDFLAGS	+= -O3 -fomit-frame-pointer -DNDEBUG -flto
endif

ifdef ALLOCWRAP
	LDFLAGS += alloc_wrap.c -DHAVE_ALLOCWRAP
	CFLAGS	+= -DHAVE_ALLOCWRAP
endif

ifdef ONLY
	TESTS2 = $(filter $(ONLY), $(TESTS))
else
	TESTS2 = $(TESTS)
endif

SRCS	= $(FILENAMES)
OBJS	= $(addprefix build/libft_, $(FILENAMES:.c=.o))

TESTTARGETS	= $(addprefix test-, $(TESTS2))
TESTBINS	= $(addprefix build/, $(TESTTARGETS))

NAME		= libft.a

.PHONY: all clean fclean re test

all: $(NAME) libftprintf.a

clean:
	rm -rf build/
	rm -f $(TESTBINS)
	make -C ft_printf clean
	@printf "\e[33m\e[1m[CLEAN]\e[m $$(basename $$(pwd))\n"

fclean: clean
	rm -f $(NAME)
	rm -f libftfuncs.a
	rm -f libftprintf.a
	make -C ft_printf fclean
	@printf "\e[33m\e[1m[FCLEAN]\e[m $$(basename $$(pwd))\n"

re: fclean
	$(MAKE) all

####
# Libraries
$(NAME): libftfuncs.a libftprintf.a
	libtool -static -o $@ $^ || $(MAKE) libft.a_linux
	@printf "\e[32m\e[1m[OK]\e[m $$(basename $@)\n"

.PHONY: libft.a_linux
libft.a_linux:
	echo create libft.a > .script
	echo addlib libftfuncs.a >> .script
	echo addlib libftprintf.a >> .script
	echo save >> .script
	echo end >> .script
	ar -M <.script
	rm .script

libftfuncs.a: $(OBJS)
	ar rcs $@ $(OBJS)
	@printf "\e[32m\e[1m[OK]\e[m $$(basename $@)\n"

libftprintf.a: ft_printf/libftprintf.a
	ln -f -s ft_printf/libftprintf.a

ft_printf/libftprintf.a:
	$(MAKE) -C ft_printf libftprintf.a

####
# Install
install: all
	mkdir -p $(PREFIX)/lib
	ln -f $(NAME) $(PREFIX)/lib/$(NAME)
	mkdir -p $(PREFIX)/include
	ln -f includes/libft.h $(PREFIX)/include/libft.h
	ln -f includes/ft_printf.h $(PREFIX)/include/ft_printf.h

install_clean:
	rm -f $(PREFIX)/lib/$(NAME)
	rm -f $(PREFIX)/include/libft.h
	rm -f $(PREFIX)/include/ft_printf.h

build/libft_%.o: %.c libft.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

build/test_%.o: tests/test_%.c libft.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTBINS)
	for bin in $(TESTBINS); do \
		echo $$bin ; \
		$$bin ; \
		echo ; \
	done

norm:
	norminette $(SRCS) libft.h | grep -e 'Warning' -e 'Error' -B1 || true

build/test-%: build/test_%.o libft.a
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $@ $^

# Without ASan

build/libft_ft_strcmp.o: ft_strcmp.c libft.h
	$(CC) $(filter-out -fsanitize=address,$(CFLAGS)) -c $< -o $@

build/libft_ft_strncmp.o: ft_strncmp.c libft.h
	$(CC) $(filter-out -fsanitize=address,$(CFLAGS)) -c $< -o $@

build/test_strcmp.o: test_strcmp.c libft.h
	$(CC) $(filter-out -fsanitize=address,$(CFLAGS)) -c $< -o $@

build/test_strncmp.o: test_strncmp.c libft.h
	$(CC) $(filter-out -fsanitize=address,$(CFLAGS)) -c $< -o $@

build/test-strcmp: build/test_strcmp.o libft.a
	@mkdir -p $(@D)
	$(CC) $(filter-out -fsanitize=address,$(LDFLAGS)) -o $@ $^

build/test-strncmp: build/test_strncmp.o libft.a
	@mkdir -p $(@D)
	$(CC) $(filter-out -fsanitize=address,$(LDFLAGS)) -o $@ $^

build/test_quentin.o: test_quentin.c libft.h
	$(CC) $(CFLAGS) -I. -c $< -o $@

