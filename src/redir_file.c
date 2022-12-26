/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:41:38 by smiro             #+#    #+#             */
/*   Updated: 2022/12/16 21:41:41 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

void	put_in_file(int type, t_cmd *cmd, char *file)
{
	int		fd;

	if (type == 1 || type == 5)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error("Error open", 44);
	if (type == 5 || type == 6)
	{
		if (dup2(fd, cmd->pipes->out_error) == -1)
			exit_error("Error dup", 45);
	}
	else
	{
		if (dup2(fd, cmd->pipes->out) == -1)
			exit_error("Error dup", 45);
	}
	free(file);
	close(fd);
}

int	get_from_file(t_cmd *cmd, char *file, int i)
{
	int		fd;
	int		pfd[2];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		put_error("bash", file, "No such file or directory");
		pipe(pfd);
		if (dup2(pfd[1], cmd->pipes->out) == -1)
			exit_error("Error dup", 50);
		if (close(pfd[0]) == -1 || close(pfd[1]) == -1)
			exit_error("Error close", 51);
		while (cmd->arg[i])
			cmd->arg = remove_one(cmd->arg, i);
		free(file);
		return (1);
	}
	else if (dup2(fd, cmd->pipes->in) == -1)
		exit_error("Error dup", 45);
	close(fd);
	free(file);
	return (0);
}

void	get_input(t_cmd *cmd, char *stop)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("Error pipe", 47);
	if (write(1, "> ", 2) == -1)
		exit_error("Error write", 48);
	line = get_next_line(cmd->pipes->in);
	while (line && ft_strncmp(line, stop, ft_strlen(stop)))
	{
		write(1, "> ", 2);
		if (write(fd[1], line, ft_strlen(line)) == -1)
			exit_error("Error write", 30);
		free(line);
		line = get_next_line(cmd->pipes->in);
	}
	free(line);
	free(stop);
	if (dup2(fd[0], cmd->pipes->in) == -1)
		exit_error("Error dup", 48);
	close(fd[0]);
	close(fd[1]);
}
