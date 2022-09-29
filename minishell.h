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

typedef struct s_list
{
	int		echo_control;
	int		quotes;
	int		num_args;
	int		num_env;
	int		control;
	//int 	cmd_lines;
	char	**argu;
	char	**ent_var;	
	char	*read_line;
	char	*prompt;
	char	*result;
	char 	*cmd_line;
}	t_list;

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		parsing(char *s, t_list *d);
int		main(int argc, char **argv, char **envp);
int		ft_echo(t_list *d);
int		check_echo_word(char *s);
int		check_env_word(char *s);
int		check_pwd_word(char *s);
int		ft_strlen(const char *s);
int		ft_unset(t_list *d);
int		ft_export(t_list *d);
int		ft_env(t_list *d);
int		ft_pwd(int i);
int		ft_cd(t_list *d);
int		parsing(char *s, t_list *d);
int 	choose_arg(char *s, t_list *d);
int		check_dolar_echo(char *line);
void	ft_free();
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		check_null_args(char *s, t_list *d, int control);
char	*change_dolar_x_var(t_list *d);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1, char set);
char	*ft_substr(char *s, int start, int len);

#endif