/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 04:23:31 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 04:23:32 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*str_tolower(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = 0;
	j = 0;
	doubles = 1;
	simples = 1;
	if (str[i] == 34 || str[i] == 39)
	{
		str = remove_quotes(str, str[i]);
		doubles = -1;
		simples = -1;
	}
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[i])
	{
		while (str[i] == 34 && simples != -1 && i++)
				doubles *= -1;
		while (str[i] == 39 && doubles != -1 && i++)
			simples *= -1;
		temp[j] = ft_tolower(str[i]);
		i++;
		j++;
	}
	return (temp);
}

static	int	cmd_type(t_cmd *args)
{
	char *cmd;
	cmd = str_tolower(args->cmd);
	if (!ft_strncmp(cmd, "echo", 4))
		ft_echo(&args);
	else if (!ft_strncmp(cmd, "cd", 2))
		ft_cd(&args);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd(0);
	else if (!ft_strncmp(cmd, "export", 6))
		ft_export(&args);
	else if (!ft_strncmp(cmd, "unset", 5))
		ft_unset(&args);
	else if (!ft_strncmp(cmd, "env", 3))
		ft_env(args);
	else if (!ft_strncmp(cmd, "exit", 5))
		printf("%s\n", cmd);
	else
		printf("1 %s\n", cmd);
	return (0);
}

void	execute_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	int	pid;
	int	i;
	int	ret;//global

	temp = *cmd;
	if (temp->flags->pipe == 0)
	{
		cmd_type(temp);
		return ;
	}
	i = 1;
	while (temp)
	{
		if (!temp->next)
			temp->pipes->last = 0;
		setfds(temp->pipes, i);
		setpipes(temp->pipes, i);
		pid = fork();
		if (pid == -1)
			exit_error("Error fork", 27);
		if (pid == 0)
		{
			dup2(temp->pipes->in, STDIN_FILENO);
			dup2(temp->pipes->out, STDOUT_FILENO);
			close(temp->pipes->in);
			close(temp->pipes->out);
			exit(cmd_type(temp));
		}
		temp = temp->next;
		i++;
	}
	while (--i)
	{
		waitpid(-1, &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		if (ret != 0 && ret != 1)
			perror(NULL);
	}
}