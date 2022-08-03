NAME = minishell

SRCS = minishell.c 

INCLUDE = minishell.h \

CC = gcc
RM = rm -f
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MMD -lreadline -L${HOME}/.brew/opt/readline/lib
#-g3 -fsanitize=address

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRCS:.c=.o}
DEPS = $(addsuffix .d, $(basename $(SRCS)))

all:	${NAME}

-include $(DEPS)
${NAME}:	${OBJS}
			$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
			${RM} ${OBJS} ${DEPS}

fclean: clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re