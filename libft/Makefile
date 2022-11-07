NAME		= libft.a
HEAD		:= -I
INCLUDES		= includes/
SRC_DIR		= srcs/
OBJ_DIR		= objs/
CC		= gcc
CFLAGS		= -Wall -Wextra -Werror
FOBJS		= *.o
RM		= rm -f
AR		= ar rcs
SRC_NAMES	:= \
			ft_isalpha \
			ft_isdigit \
			ft_isalnum \
			ft_isascii \
			ft_isprint \
			ft_strlen \
			ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strcpy \
			ft_strncpy \
			ft_strlcpy \
			ft_strlcat \
			ft_toupper \
			ft_tolower \
			ft_strchr \
			ft_strrchr \
			ft_strncmp \
			ft_memchr \
			ft_memcmp \
			ft_strstr \
			ft_strnstr \
			ft_atoi \
			ft_atoi_base \
			ft_atoi_u \
			ft_atoll \
			ft_calloc \
			ft_realloc \
			ft_swap \
			ft_strdup \
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_abs \
			ft_itoa \
			ft_strmapi \
			ft_striter \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_lstnew \
			ft_lstadd_front \
			ft_lstsize \
			ft_lstlast \
			ft_lstadd_back \
			ft_lstdelone \
			ft_lstclear \
			ft_lstiter \
			ft_lstmap \
			ft_lstarr \
			ft_lstelemi \
			ft_get_next_line

# COLORS

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


SRC 		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_NAMES)))

OBJ 		= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_NAMES)))

OBJF		= .cache_exists

all: $(NAME)

$(NAME):	$(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(GREEN)Libft compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c includes/libft.h Makefile | $(OBJF)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(HEAD) $(INCLUDES) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -f $(OBJF)
	@echo "$(BLUE)Libft objects files cleaned!$(DEF_COLOR)"

fclean:	clean
	@$(RM) -f $(NAME)
	@echo "$(CYAN)Libft executable files cleaned!$(DEF_COLOR)"


re:	fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for libft!$(DEF_COLOR)"

norm:
	@norminette $(SRC) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
