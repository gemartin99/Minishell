################################################################################
### INIT
################################################################################

NAME		= minishell
INC			= ./inc/
INC_HEADERS	= $(INC)minishell.h

FT_INC		= $(FT)includes/libft.h

FT			= ./libft/
FT_LNK		= -L$(FT) -lft
FT_LIB		= $(FT)libft.a

SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= gcc
COMFLAGS = -I/usr/local/opt/readline/include
LINKFLAGS = -lreadline -L/usr/local/opt/readline/lib
CFLAGS		= -I $(INC) -MMD#-Wall -Werror -Wextra -fsanitize=address
RM			= rm -f

################################################################################
### COLORS
################################################################################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

################################################################################
### OBJECTS
################################################################################

SRC_FILES	=	main \
				ft_free \
				ft_pwd \
				ft_unset \
				ft_parsing \
				ft_export \
				ft_exit \
				ft_env \
				ft_echo_dolar \
				ft_echo \
				ft_cd \
				check_command_name

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
B_OBJ		=	$(OBJ)

OBJF		=	.cache_exists

################################################################################
### RULES
################################################################################


all:		$(NAME)

$(OBJF):
			@mkdir -p $(OBJ_DIR)

$(FT_LIB):	$(FT_INC) $(FT)srcs/*.c $(FT)Makefile
			@make -C $(FT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_HEADERS) $(FT_LIB) Makefile | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) $(COMFLAGS) $(LINKFLAGS) -o $(NAME)
			@echo "$(GREEN)Minishell compiled!$(DEF_COLOR)"

bonus:		$(B_OBJ) $(NAME)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(FT)
			@echo "$(BLUE)Minishell object files cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f lib*.a
			@make fclean -C $(FT)
			@echo "$(CYAN)Minishell executable files cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for fdf!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INC)minishell.h $(FT) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
