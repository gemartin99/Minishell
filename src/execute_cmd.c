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

static	int	cmd_type(t_cmd *cmd, char *temp_cmd)
{
	if (!ft_strncmp(temp_cmd, "cd", 2))
		ft_cd(&cmd);
	else if (!ft_strncmp(temp_cmd, "export", 6))
		ft_export(&cmd);
	else if (!ft_strncmp(temp_cmd, "unset", 5))
		ft_unset(&cmd);
	else if (!ft_strncmp(temp_cmd, "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(str_tolower(temp_cmd), "pwd", 3))
		ft_pwd(0);
	else if (!ft_strncmp(str_tolower(temp_cmd), "env", 3))
		ft_env(cmd);
	else if (!ft_strncmp(str_tolower(temp_cmd), "echo", 4))
		ft_echo(&cmd);
	else if (!ft_strncmp(temp_cmd, "cd", 2))
		return (0);
	else
		ft_try_to_exec(cmd);
	free(temp_cmd);
	return (0);
}

static void cmd_process(t_cmd *cmd, char *temp_cmd)
{
	if (dup2(cmd->pipes->in, STDIN_FILENO) == -1)
		exit_error("Error DUP", 23);
	if (dup2(cmd->pipes->out, STDOUT_FILENO) == -1)
		exit_error("Error DUP", 24);
	if (close(cmd->pipes->in) == -1)
		exit_error("Error close", 25);
	if (close(cmd->pipes->out) == -1)
		exit_error("Error close", 26);
	exit(cmd_type(cmd, temp_cmd));
}


static int	check_nonpipables(t_cmd *cmd, char *temp_cmd)
{
	if (cmd->next)
		return (0);
	if (!ft_strncmp(temp_cmd, "export", 6))
			return (1);
	else if (!ft_strncmp(temp_cmd, "unset", 5))
			return (1);
	return (0);
}

void	execute_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	int	pid;
	int	i;
	char *temp_cmd;
	int	ret;

	temp = *cmd;
	temp_cmd = str_noquotes(temp->cmd);
	if (check_nonpipables(temp, temp_cmd))
	{
		cmd_type(temp, temp_cmd);
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
			cmd_process(temp ,temp_cmd);
		temp = temp->next;
		i++;
	}
	
	// HACER FUNCION WAIT PROCESS Y GET ERRORS
	while (--i)
	{
		waitpid(-1, &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
		if (ret != 0 && ret != 1)
			perror(NULL);
	}
}