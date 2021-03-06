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
	int		quotes;
	int		num_args;
	int 	num_env;
	char	**argu;
	char	**ent_var;	
	char	*read_line;
	char	*prompt;
}	t_list;

int main(int argc, char **argv, char **envp);

#endif