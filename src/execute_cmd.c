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
#include "../inc/libft/libft.h"

static	int	cmd_type(t_cmd *cmd, char *temp_cmd)
{
	if (!ft_strncmp(temp_cmd, "~", 2))
	{
		printf("bash: %s: is a directory\n", getenv("HOME"));
		return (126);
	}
	else if (!ft_strncmp(temp_cmd, "cd", 3))
		return (ft_cd(&cmd));
	else if (!ft_strncmp(temp_cmd, "export", 7))
		return (ft_export(&cmd));
	else if (!ft_strncmp(temp_cmd, "unset", 6))
		return (ft_unset(&cmd));
	else if (!ft_strncmp(temp_cmd, "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(str_tolower(temp_cmd), "pwd", 4))
		return (ft_pwd(0));
	else if (!ft_strncmp(str_tolower(temp_cmd), "env", 4))
		return (ft_env(cmd));
	else if (!ft_strncmp(str_tolower(temp_cmd), "echo", 5))
		return (ft_echo(&cmd));
	else if (!ft_strncmp(temp_cmd, "cd", 3))
		return (0);
	else
		return (ft_try_to_exec(cmd));
	free(temp_cmd);
	return (1);
}

static void	cmd_process(t_cmd *cmd, char *temp_cmd)
{
	if (dup2(cmd->pipes->out_error, STDERR_FILENO) == -1)
		exit_error("Error DUP", 23);
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

static void	wait_exit(t_pipe *pipes, int i, int pid)
{
	int	temp_pid;
	int	temp;

	if (close(pipes->in) == -1)
		exit_error("Error close", 51);
	if (close(pipes->out) == -1)
		exit_error("Error close", 52);
	free(pipes);
	while (--i)
	{
		temp_pid = waitpid(-1, &g_error, 0);
		if (WIFEXITED(g_error))
			g_error = WEXITSTATUS(g_error);
		if (temp_pid == pid)
			temp = g_error;
		if (g_error == 2 || g_error == 3)
			g_error = g_error + 128;
		else if (g_error != 0 && g_error != 1 && g_error != 127
			&& g_error != 13 && g_error != 126)
			perror(NULL);
	}
	g_error = temp;
	wait_signal(1);
}

void	execute_nonpipe(t_cmd *cmd, char *temp_cmd)
{
	int	io[2];

	cmd->pipes = init_pipes();
	cmd->pipes->last = 0;
	setfds(cmd->pipes, 1);
	setpipes(cmd->pipes, 1);
	if (dup2(STDIN_FILENO, io[0]) == -1 || dup2(STDOUT_FILENO, io[1]) == -1)
		exit_error("Error DUP", 23);
	if (cmd->arg && is_redir(cmd->arg) != -1)
		redir(cmd);
	if (dup2(cmd->pipes->in, STDIN_FILENO) == -1
		|| dup2(cmd->pipes->out, STDOUT_FILENO) == -1)
		exit_error("Error DUP", 24);
	if (close(cmd->pipes->in) == -1 || close(cmd->pipes->out) == -1)
		exit_error("Error close", 26);
	g_error = cmd_type(cmd, temp_cmd);
	if (dup2(io[0], STDIN_FILENO) == -1 || dup2(io[1], STDOUT_FILENO) == -1)
		exit_error("Error DUP", 24);
	free(temp_cmd);
	// clear_lst(&cmd);
	return ;
}

void	execute_cmd(t_cmd **cmd, t_pipe *pipes)
{
	int			pid;
	int			i;
	char		*temp_cmd;

	i = 1;
	wait_signal(0);
	while ((*cmd))
	{
		temp_cmd = str_noquotes((*cmd)->cmd);
		if (!(*cmd)->next)
			pipes->last = 0;
		setfds(pipes, i);
		setpipes(pipes, i++);
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
	clear_lst(cmd);
	wait_exit(pipes, i, pid);
}
