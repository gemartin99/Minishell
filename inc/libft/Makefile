# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seba <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 11:39:14 by seba              #+#    #+#              #
#    Updated: 2022/10/31 22:34:51 by smiro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

MKFL	= Makefile

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcpy.c ft_memcmp.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OBJS	= $(SRCS:.c=.o)

RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -I.

%.o: %.c libft.h $(MKFL)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r                                                                           "
	@printf "\r ⚙️  ${CC} ${CFLAGS} -I./ -c $< -o $@"

all:
	@$(MAKE) $(NAME)

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\nCompiled\n"

clean:	
	$(RM) $(NAME) $(OBJS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re
