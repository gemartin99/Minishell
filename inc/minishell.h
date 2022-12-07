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

typedef struct s_token
{
	char	*tkn;
	int		type;
	struct s_token	*next;
}							t_token;

typedef struct s_cmd
{
	char	**arg;
	char	**env;
	char	*path;
	int		num_arg;
	int		num_env;
}							t_cmd;

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
	t_token	*tokens;
	t_cmd		*cmd;
	t_flags	*flags;
}							t_msh;

void	exit_error(char *str, int n);
t_msh	*init(char **env);
void	many_args(char **argv);
void	recive_arguments(t_msh *msh);

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
