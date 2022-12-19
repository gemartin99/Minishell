# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seba <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/11 11:39:14 by seba              #+#    #+#              #
#    Updated: 2022/11/25 16:58:32 by smiro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
BNUS	= .bonus

MKFL	= Makefile

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcpy.c ft_memcmp.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

BONUS	=	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

BONUS_OBJS	= $(BONUS:.c=.o)

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
	
bonus:
	@$(MAKE) $(BNUS)

$(BNUS): $(OBJS) $(BONUS_OBJS)
	@touch $@
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:	
	$(RM) $(NAME) $(OBJS) $(BONUS_OBJS)

fclean:
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re bonus
