/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 05:27:11 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 05:27:13 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_count_args(char *s) //funcion que cuenta el numero de argumentos que me mandan
{
	int i;
	int res;

	i = -1;
	res = 0;
	while (s[++i])
	{
		if ((s[i] != 32 && s[i] != 34 && s[i] != 39) && (s[i + 1] == 32 || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
			res++;
		if (s[i] == 34)
		{
			res++;
			while (s[++i] && s[i] != 34)
				;
		}
		if (s[i] == 39)
		{
			res++;
			while (s[++i] && s[i] != 39)
				;
			i++;
		}
	}
	return (res);
}

char **ft_get_args(char *s, t_cmd *cmd)
{
	int i;
	char **res;

	i = -1;
	cmd->num_arg = ft_count_args(s);
	while (check_null_args(s, 0) == -1)
		s = change_null_args(s, cmd);
	res = malloc(sizeof(char *) * (cmd->num_arg + 1));
	while(s[++i])
	{
		return (NULL);
	}
	return (NULL);
}

static char *get_comand(char *read_line)
{
	int	i;
	int	start;
	char	*str;

	i = 0;
	while (read_line[i] == 32 || (read_line[i] >= 9 && read_line[i] <= 13))
		i++;
	start = i;
	while (read_line[i] && read_line[i] != 32 
			&& !(read_line[i] >= 9 && read_line[i] <= 13))
	{
		if (read_line[i] == 34 || read_line[i] == 39)
			i = get_next_quote(i, str, read_line[i]);
		i++;
	}
	str = ft_substr(read_line, start, i);
	read_line += i;
	return (str);
}

static t_cmd	*add_cmd(char *read_line)
{
	t_cmd *temp;

	temp = ft_calloc(sizeof(t_cmd), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	temp->cmd = get_comand(read_line);
	printf("cmd %s\n", temp->cmd);
	temp->arg = ft_get_args(read_line, temp);
	temp->next = NULL;
	return (temp);
}

/*
static void	tokenize(t_msh *msh, char *read_line)
{
	int prueba;
	char **test;

	msh->flags->pipe = ft_count_pipes(read_line);
	//if (pipe == 0)
	//	msh->cmd->arg = ft_get_args(read_line, msh->cmd);
	//else
	msh->cmd->arg = ft_get_args(read_line, msh->cmd)
	exit (0);
}*/

static void	tokenize(t_msh *msh, char *read_line) //
{
	int i;
	t_cmd	*temp;

	temp = msh->cmd;
	i = -1;
	msh->flags->pipe = ft_count_pipes(read_line);
	while (++i <= msh->flags->pipe)
	{
		temp = add_cmd(read_line);
		temp = temp->next;
	}
}

void	recive_arguments(t_msh *msh)
{
	char	*read_line;
	
	while (1)
	{
		read_line = readline( BLUE_T "Mi" WHITE_T "ni" YELLOW_T "s"
				WHITE_T "he" BLUE_T "ll" "🇦🇷 🧉->" RESET_COLOR);
		if (!read_line)
			exit_error("exit", 0);
		if (read_line[0] == '\0')
			printf("");
		else
		{
			add_history(read_line);
			tokenize(msh, read_line);
		}
	}
}
