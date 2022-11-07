/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:22:14 by gemartin          #+#    #+#             */
/*   Updated: 2022/09/14 11:22:42 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

/*
# include<unistd.h>
# include<stdlib.h>
# include<limits.h>
# include<stdio.h>
# include<string.h>
# include<sys/param.h> //para el maxpathlen de pwd
# include <readline/readline.h>
# include <readline/history.h>*/

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

typedef struct s_msh
{
	int 		i;
	int 		atoi_error;
	int			echo_control;
	int			quotes;
	int			num_args;
	int			num_env;
	int			control;
	int 		control_var_reminder;
	int 		quote_lvl;
	//int 	cmd_lines;
	int 		dolar_question; //variable $?
	char		**argu;
	char		**ent_var;
	char		*read_line;
	char		*prompt;
	char		*result;
	char 		*cmd_line;
	char 		*var_reminder;
	char		*path_value;
}				t_msh; // t_minishell

int		ft_strcmp(char *s1, char *s2);
int		parsing(char *s, t_msh *d);
int		main(int argc, char **argv, char **envp);
int		ft_echo(t_msh *d);
int		check_echo_word(char *s);
int		check_env_word(char *s);
int		check_pwd_word(char *s);
int		ft_unset(t_msh *d);
int		ft_export(t_msh *d);
int		ft_env(t_msh *d);
int		ft_pwd(int i);
int		ft_cd(t_msh *d);
int 	choose_arg(char *s, t_msh *d);
int		check_dolar_echo(char *line);
void	ft_exit(t_msh *d);
void	ft_free();
int		check_null_args(char *s, t_msh *d, int control);
char	*change_dolar_x_var(t_msh *d);

#endif
