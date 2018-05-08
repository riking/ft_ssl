# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/09 19:11:26 by kyork             #+#    #+#              #
#    Updated: 2018/05/07 19:15:32 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

ARCH		?= $(shell uname -m)
OS			?= $(shell uname -s | tr A-Z a-z)

FILENAMES	+= do_printf.c ft_strichr.c printer.c strout.c
FILENAMES	+= parse_fmt.c parse_numflag.c
FILENAMES	+= out_chr.c out_dec.c out_base.c out_pct.c
FILENAMES	+= dprintf.c snprintf.c asprintf.c perrorf.c

OBJS		= $(addprefix build/ft_printf_, $(FILENAMES:.c=.o))

CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
#CFLAGS		= -Wall -Wextra -Wfloat-equal -Wundef -Wint-to-pointer-cast -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wcast-qual -Wmissing-prototypes -Wstrict-overflow=5 -Wwrite-strings -Wconversion --pedantic-errors
CFLAGS		+= -I includes/
LDFLAGS		+= -Wall -Wextra

DYNCALL_PATH	= ../extern/dyncall-0.9-release

ifndef NO_WERROR
	CFLAGS += -Werror
	LDFLAGS += -Werror
endif

ifeq ($(OS),darwin)
	VERSION = darwin
else
	VERSION = generic
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): libftprintf_$(VERSION).o
	ar rcs $(NAME) $<
	@printf "\e[32m\e[1m[OK]\e[m $$(basename $@)\n"

libftprintf_darwin.o: exported_darwin.sym $(OBJS)
	ld -o $@ -r -exported_symbols_list exported_darwin.sym $(OBJS)

libftprintf_generic.o: $(OBJS)
	ld -o $@ -r $(OBJS)

exported_darwin.sym: exported.sym
	<$^ sed "s/^/_/" >$@

clean:
	rm -rf build
	rm -f exported_darwin.sym
	rm -f libftprintf_darwin.o libftprintf_generic.o
	@printf "\e[33m\e[1m[CLEAN]\e[m $$(basename $$(pwd))\n"

fclean: clean
	rm -f $(NAME)
	@printf "\e[33m\e[1m[FCLEAN]\e[m $$(basename $$(pwd))\n"

re: fclean
	$(MAKE) all

build:
	mkdir -p build

build/ft_printf_%.o: srcs/%.c srcs/*.h | build
	$(CC) $(CFLAGS) -c -o $@ $<

build/small_test.o: tests/small_test.c | build
	$(CC) $(CFLAGS) -c $< -o $@

smalltest: build/small_test.o $(NAME) | build
	$(CC) $(LDFLAGS) -o $@ build/small_test.o -L. -lftprintf

build/nm_test.o: tests/nm_test.c srcs/*.h | build
	$(CC) $(CFLAGS) -c -o $@ $<

nm_test: build/nm_test.o $(NAME)
	$(CC) $(LDFLAGS) -o $@ build/nm_test.o -L. -lftprintf

build/fuzz_main.o: tests/fuzz_main.c srcs/*.h | build
	$(CC) $(CFLAGS) -c $< -o build/small_test.o -I ../libft/includes -I $(DYNCALL_PATH)/include

fuzzmain: build/fuzz_main.o $(NAME) | build
	$(CC) $(LDFLAGS) -o $@ build/small_test.o -L. -lftprintf -L ../libft -lft -L $(DYNCALL_PATH)/lib -ldyncall_s
