/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:29:00 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:29:01 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	newpipe(int *fd)
{
	if (close(fd[0]) == -1)
		exit(2);
	if (close(fd[1]) == -1)
		exit(3);
	pipe(fd);
}

void	setpipes(t_pipe *pipes, int i)
{
	if (i == 0)
		return ;
	else if (i % 2)
		newpipe(pipes->fd[1]);
	else
		newpipe(pipes->fd[0]);
}

static void	duppipe(int *io, int fd)
{
	if (close(*io) == -1)
		exit(4);
	*io = dup(fd);
	if (*io == 1)
		exit(5);
}

void	setfds(t_pipe *pipe, int i)
{
	duppipe(&(pipe->in), STDIN_FILENO);
	duppipe(&(pipe->out), STDOUT_FILENO);
	if (i == 0)
		return ;
	else if (i % 2)
	{
		if (i != 1)
			duppipe(&(pipe->in), pipe->fd[1][0]);
		if (pipe->last)
			duppipe(&(pipe->out), pipe->fd[0][1]);
	}
	else
	{
		duppipe(&(pipe->in), pipe->fd[0][0]);
		if (pipe->last)
			duppipe(&(pipe->out), pipe->fd[1][1]);
	}
}

t_pipe	*init_pipes(void)
{
	t_pipe	*pipes;

	pipes = ft_calloc(sizeof(t_pipe), 1);
	pipe(pipes->fd[0]);
	pipe(pipes->fd[1]);
	pipes->in = dup(STDIN_FILENO);
	pipes->out = dup(STDOUT_FILENO);
	pipes->last = 1;
	return (pipes);
}
