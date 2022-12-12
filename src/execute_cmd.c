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

static	int	cmd_type(t_cmd *args) //???? Args es CMD
{
	char *cmd;
	cmd = str_noquotes(args->cmd);
	if (!ft_strncmp(cmd, "cd", 2))
		ft_cd(&args);
	else if (!ft_strncmp(cmd, "export", 6))
		ft_export(&args);
	else if (!ft_strncmp(cmd, "unset", 5))
		ft_unset(&args);
	else if (!ft_strncmp(cmd, "exit", 5))
		ft_exit(args);
	else if (!ft_strncmp(str_tolower(cmd), "pwd", 3))
		ft_pwd(0);
	else if (!ft_strncmp(str_tolower(cmd), "env", 3))
		ft_env(args);
	else if (!ft_strncmp(str_tolower(cmd), "echo", 4))
		ft_echo(&args);
	else if (!ft_strncmp(cmd, "cd", 2)) // Es para cd en mayuscula, probalo en bash
		return (0);
	else
		ft_try_to_exec(args);
	free(cmd);
	return (0);
}

static void cmd_process(t_cmd *cmd)
{
	if (dup2(cmd->pipes->in, STDIN_FILENO) == -1)
		exit_error("Error DUP", 23);
	if (dup2(cmd->pipes->out, STDOUT_FILENO) == -1)
		exit_error("Error DUP", 24);
	if (close(cmd->pipes->in) == -1)
		exit_error("Error close", 25);
	if (close(cmd->pipes->out) == -1)
		exit_error("Error close", 26);
	exit(cmd_type(cmd));
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
			cmd_process(temp);
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