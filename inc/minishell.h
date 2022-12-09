/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 02:22:16 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 02:22:19 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<dirent.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<signal.h>
# include	<limits.h>
# include	<termios.h>
# include	<dirent.h>
# include	<sys/stat.h>
# include	<sys/ioctl.h>
# include	<sys/param.h>
# include "libft/libft.h"

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	int		num_arg;
	struct s_cmd	*next;
}							t_cmd;

typedef struct s_env
{
	char	**env;
	char	*path;
	int		num_env;
}							t_env;

typedef struct s_flags
{
	int	quote;
	int	pipe;
	int	redic;
	int	dollar;
}							t_flags;

typedef struct s_msh
{
	int	bash_lvl;
	int	total_chars;
	t_cmd	*cmd;
	t_env		*env;
	t_flags	*flags;
}							t_msh;

void	exit_error(char *str, int n);
t_msh	*init(char **env);
void	many_args(char **argv);
void	recive_arguments(t_msh *msh);
int 	ft_count_pipes(char *s);
char	*change_null_args(char *s, t_cmd *cmd);
int		check_null_args(char *s);
int		get_next_quote(int i, char *str, char c);
int		ft_check_dquote(char *s, int simple, int doble, t_msh *msh);
int 	ft_count_args(char *s);
void	cmd_type(t_msh *msh);
void 	expand(t_cmd *cmd);
int 	ft_skip_space(char *s, int i);
t_cmd	*ft_last(t_cmd **cmd);
void	ft_echo(t_cmd	**cmd);
char	*remove_quotes(char *str, char c);

#define WHITE_T   "\x1b[1;37m"
#define YELLOW_T "\x1b[1;33m"
#define RESET_COLOR    "\x1b[0m"
#define BLUE_T "\x1b[1;36m"

#define COMMAND 0
#define FLAG 1
#define ARG 2
#define PIPE 3
#define REDIC 4

#endif