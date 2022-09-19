NAME = minishell

SRCS = minishell.c ft_echo.c ft_unset.c ft_export.c ft_cd.c ft_env.c ft_pwd.c \
		ft_strlen.c ft_substr.c ft_strcmp.c ft_strjoin.c ft_strlcpy.c \
		ft_strdup.c ft_strncmp.c ft_strtrim.c ft_free.c ft_parsing.c check_command_name.c \

INCLUDE = minishell.h \

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MMD
COMFLAGS = -I${HOME}/.brew/opt/readline/include
LINKFLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
#-g3 -fsanitize=address

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}
DEPS = $(addsuffix .d, $(basename $(SRCS)))

all:	${NAME}

-include $(DEPS)
${NAME}:	${OBJS}
			$(CC) $(CFLGS) $(COMFLAGS) $(LINKFLAGS) $(OBJS) -o $(NAME)

clean:
			${RM} ${OBJS} ${DEPS}

fclean: clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re