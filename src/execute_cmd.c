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
		return (ft_cd(&cmd));
	else if (!ft_strncmp(temp_cmd, "export", 6))
		return (ft_export(&cmd));
	else if (!ft_strncmp(temp_cmd, "unset", 5))
		return (ft_unset(&cmd));
	else if (!ft_strncmp(temp_cmd, "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(str_tolower(temp_cmd), "pwd", 3))
		return (ft_pwd(0));
	else if (!ft_strncmp(str_tolower(temp_cmd), "env", 3))
		return (ft_env(cmd));
	else if (!ft_strncmp(str_tolower(temp_cmd), "echo", 4))
		return (ft_echo(&cmd));
	else if (!ft_strncmp(temp_cmd, "cd", 2))
		return (0);
	else
		return (ft_try_to_exec(cmd));
	free(temp_cmd);
	return (0);
}

static void	cmd_process(t_cmd *cmd, char *temp_cmd)
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

static void	wait_exit(int i)
{
	while (--i)
	{
		waitpid(-1, &g_error, 0);
		if (WIFEXITED(g_error))
			g_error = WEXITSTATUS(g_error);
		if (g_error != 0 && g_error != 1)
			perror(NULL);
	}
}

void	execute_nonpipe(t_cmd *cmd, char *temp_cmd)
{
	if (cmd->arg && is_redir(cmd->arg) != -1)
		redir(cmd);
	g_error = cmd_type(cmd, temp_cmd);
	free(temp_cmd);
	return ;
}

void	execute_cmd(t_cmd **cmd, t_pipe *pipes)
{
	int			pid;
	int			i;
	char		*temp_cmd;

	i = 1;
	while ((*cmd) && i++)
	{
		temp_cmd = str_noquotes((*cmd)->cmd);
		if (!(*cmd)->next)
			pipes->last = 0;
		setfds(pipes, i);
		setpipes(pipes, i);
		(*cmd)->pipes = pipes;
		if ((*cmd)->arg && is_redir((*cmd)->arg) != -1)
			redir((*cmd));
		pid = fork();
		if (pid == -1)
			exit_error("Error fork", 27);
		if (pid == 0)
			cmd_process((*cmd), temp_cmd);
		(*cmd) = (*cmd)->next;
		free(temp_cmd);
	}
	free(pipes);
	wait_signal();
	wait_exit(i);
}
