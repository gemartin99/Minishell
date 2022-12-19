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

void	put_in_file(int type, t_cmd *cmd, char *file)
{
	int		fd;
	char	*temp;

	temp = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	getcwd(temp, MAXPATHLEN);
	temp = ft_strjoin(temp, "/");
	if (type == 1)
		fd = open(ft_strjoin(temp, file), O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(ft_strjoin(temp, file), O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit_error("Error open", 44);
	if (dup2(fd, cmd->pipes->out) == -1)
		exit_error("Error dup", 45);
	free(temp);
	close(fd);
}

int	get_from_file(t_cmd *cmd, char *file)
{
	int		fd;
	char	*temp;

	temp = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	getcwd(temp, MAXPATHLEN);
	temp = ft_strjoin(temp, "/");
	fd = open(ft_strjoin(temp, file), O_RDONLY);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		perror(NULL);
		if (dup2(cmd->pipes->fd[0][0], cmd->pipes->out) == -1)
			exit_error("Error dup", 50);
		return (1);
	}
	else if (dup2(fd, cmd->pipes->in) == -1)
		exit_error("Error dup", 45);
	free(temp);
	close(fd);
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
	if (dup2(fd[0], cmd->pipes->in) == -1)
		exit_error("Error dup", 48);
	close(fd[0]);
	close(fd[1]);
}
