# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/09 19:11:26 by kyork             #+#    #+#              #
#    Updated: 2018/04/30 13:23:35 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl

FILENAMES	+= main.c

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

