# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/07 04:53:46 by smiro             #+#    #+#              #
#    Updated: 2022/12/10 00:22:44 by smiro            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
### INIT
################################################################################

NAME		= minishell
INC			= ./inc/
INC_HEADERS	= $(INC)minishell.h

FT_INC		= $(FT)/libft.h

FT			= $(INC)libft/
FT_LNK		= -L$(FT) -lft
FT_LIB		= $(FT)libft.a

SRC_DIR		= src/
OBJ_DIR		= obj/
COMFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include
LINKFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
CFLAGS		= -I $(INC) -MMD -Wall -Werror -Wextra #-fsanitize=address
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

SRC_FILES	=	minishell \
				init \
				error_manager \
				handle_args \
				utils_args \
				delete_null_args \
				execute_cmd \
				utils \
				expand \
				expand_utils \
				ft_echo \
				ft_cd \
				ft_pwd \
				ft_env \
				ft_unset \
				ft_export \
				pipes \
				ft_execve \
				ft_exit \
				signals \
				only_export \
				redir \
				redir_utils \
				redir_file \
				utils_pipes


SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
B_OBJ		=	$(OBJ)

OBJF		=	.cache_exists

################################################################################
### RULES
################################################################################


all:
		@$(MAKE) -C $(FT)
		@$(MAKE) $(NAME)

$(OBJF):
			@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_HEADERS) $(FT_LIB) Makefile | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(COMFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) $(LINKFLAGS) -o $(NAME)
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

