# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/09 19:11:26 by kyork             #+#    #+#              #
#    Updated: 2018/05/06 14:42:05 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl

FILENAMES	+= main.c operations.c optparse.c
FILENAMES	+= md5/main.c md5/block.c md5/finish.c md5/md5_roundconf.c md5/vtable.c md5/write.c
FILENAMES	+= sha256/main.c sha256/finish.c sha256/round.c sha256/vtable.c sha256/write.c
FILENAMES	+= hmac/create.c hmac/write.c
FILENAMES	+= hashmain/opts.c hashmain/run.c hashmain/hmac.c

OBJS		= $(addprefix build/, $(FILENAMES:.c=.o))

LIBS		= libft/libft.a

# Flags start
CFLAGS		+= -Wall -Wextra -Wmissing-prototypes
CFLAGS		+= -I include/
LDFLAGS		+= -Wall -Wextra

ifndef NO_WERROR
	CFLAGS += -Werror
	LDFLAGS += -Werror
endif

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
	LDFLAGS += -fsanitize=address -g
endif

ifdef RELEASE
	CFLAGS += -O2
	LDFLAGS += -O2
endif
# Flags end

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $^

libft/libft.a: libft/.git/refs/heads/master
	$(MAKE) -C libft libft.a

libft/.git/refs/heads/master:
	# ignore

clean:
	rm -rf build/
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean
	$(MAKE) all

build/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

