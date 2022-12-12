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

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
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
# include	<readline/readline.h>
# include	<readline/history.h>

typedef struct	s_pipe
{
	int	fd[2][2];
	int	in;
	int	out;
	int	last;
}							t_pipe;

typedef struct	s_env
{
	char	**env;
	char	*path;
	int		num_env;
}							t_env;

typedef struct	s_flags
{
	int	quote;
	int	pipe;
	int	redic;
	int	dollar_special;
}							t_flags;

typedef struct	s_cmd
{
	char	*cmd;
	char	**arg;
	int		num_arg;
	struct s_cmd	*next;
	t_env	*env;
	t_flags	*flags;
	t_pipe	*pipes;
}							t_cmd;


typedef struct	s_msh
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
void	execute_cmd(t_cmd **cmd);
void 	expand(t_cmd **cmd);
int 	ft_skip_space(char *s, int i);
t_cmd	*ft_last(t_cmd **cmd);
void	ft_echo(t_cmd	**cmd);
char	*remove_quotes(char *str, char c);

///////////pipes/////////////////

t_pipe	*init_pipes(void);
void	setfds(t_pipe *pipe, int i);
void	setpipes(t_pipe *pipes, int i);
void	wait_signal(void);

////////expand_utils ⬇️////////

char *ft_strjoin_special(char *s1, char *s2, size_t i, size_t c);
int position_dolar(char *line);
int check_special_char(char c);
int ft_isdigit_special(int i);
int var_strcmp(char *s1, char *s2);
char	*str_tolower(char *str);
char	*str_noquotes(char *str);


////////builtins️////////


int	ft_cd(t_cmd **cmd);

int	ft_pwd(int i);

int	ft_env(t_cmd *cmd);

void	ft_unset(t_cmd **cmd);

int ft_export(t_cmd **cmd);

int ft_try_to_exec(t_cmd *cmd);

void	ft_exit(t_cmd *cmd);

#define WHITE_T   "\x1b[1;37m"
#define YELLOW_T "\x1b[1;33m"
#define RESET_COLOR    "\x1b[0m"
#define BLUE_T "\x1b[1;36m"

#endif