/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:35:29 by smiro             #+#    #+#             */
/*   Updated: 2022/12/22 11:35:33 by smiro            ###   ########.fr       */
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

int	g_error;

typedef struct s_pipe
{
	int	fd[2][2];
	int	in;
	int	out;
	int	last;
}							t_pipe;

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
	int	dollar_special;
}							t_flags;

typedef struct s_cmd
{
	struct s_cmd	*next;
	t_env			*env;
	t_flags			*flags;
	t_pipe			*pipes;
	char			*cmd;
	char			**arg;
	int				num_arg;
}							t_cmd;

typedef struct s_msh
{
	int		bash_lvl;
	int		total_chars;
	t_cmd	*cmd;
	t_env	*env;
	t_flags	*flags;
}							t_msh;

void	exit_error(char *str, int n);
t_msh	*init(char **env);
void	many_args(char **argv);
void	recive_arguments(t_msh *msh);
int		ft_count_pipes(char *s);
char	*change_null_args(char *s, t_cmd *cmd);
int		check_null_args(char *s);
int		get_next_quote(int i, char *str, char c);
int		ft_check_dquote(char *s, int simple, int doble, t_msh *msh);
int		ft_count_args(char *s);
void	execute_cmd(t_cmd **cmd, t_pipe *pipes);
void	expand(t_cmd **cmd);
t_cmd	*ft_last(t_cmd **cmd);
void	get_input(t_cmd *cmd, char *stop);
int		start_line(t_msh **msh, char *read_line, char ***lines);
void	put_error(char *bash, char *file, char *error);
int		export_parse(t_cmd *cmd, char *array, int j, int control);
int		tokenize(t_msh *msh, t_cmd **cmd, char *read_line);

///////////pipes/////////////////

t_pipe	*init_pipes(void);
void	setfds(t_pipe *pipe, int i);
void	setpipes(t_pipe *pipes, int i);
void	wait_signal(int i);
char	**ft_split_pipes(char *s);

//////////redirection///////////

int		is_redir(char **arg);
int		redir_type(char *str);
int		isdifoperator(char c);
char	operator_char(int n);
void	redir(t_cmd	*cmd);
int		get_next_diff(int i, char *str);
void	put_in_file(int type, t_cmd *cmd, char *file);
int		get_from_file(t_cmd *cmd, char *file);
int		check_nonpipables(t_cmd *cmd, char *temp_cmd);
void	execute_nonpipe(t_cmd *cmd, char *temp_cmd);

////////expand_utils ⬇️////////

char	*ft_strjoin_special(char *s1, char *s2, size_t i, size_t c);
int		check_special_char(char c);
int		ft_isdigit_special(int i);
int		var_strcmp(char *s1, char *s2);
char	*str_tolower(char *str);
char	*str_noquotes(char *str);
char	*ft_replace_value(char *s);
int		check_dolar(char *line);
int		check_dolar_and_digit(char *s);
char	*ft_name_var(char *line);
char	*ft_split_var(char *line, int i, t_cmd *cmd);
char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder);
char	*change_dolar_x_var(t_cmd *cmd, char *s);
char	*ft_add_var_value(char *s1);
char	*change_line_value(char *line, char *var);
char	*quit_dollar_and_digit(char *s, int i, int j);
char	*cmp_name_var(t_cmd *cmd, char *line, char *name_var);

////////env_utils///////////

int		ft_count_env(char **arg, int len);
int		check_only_space(char *s);

////////utils////////////

int		ft_isdigit_special(int i);
int		check_special_char(char c);
int		ft_skip_space(char *s, int i);
char	*remove_quotes(char *str, char c);
int		search_next_char(char *s, char c, int i);

////////builtins️////////

int		ft_cd(t_cmd **cmd);

int		ft_pwd(int i);

int		ft_env(t_cmd *cmd);

int		ft_unset(t_cmd **cmd);

int		ft_export(t_cmd **cmd);
void	print_export_var(t_cmd *cmd);

int		ft_try_to_exec(t_cmd *cmd);

void	ft_exit(t_cmd *cmd);

int		ft_echo(t_cmd	**cmd);

# define WHITE_T   "\x1b[1;37m"
# define YELLOW_T "\x1b[1;33m"
# define RESET_COLOR    "\x1b[0m"
# define BLUE_T "\x1b[1;36m"

#endif
