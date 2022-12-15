/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:41:33 by smiro             #+#    #+#             */
/*   Updated: 2022/12/12 23:41:57 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //Hacer 
// char	*get_filename(char **arg, int i, char c)
// {
// 	char	**file;
// 	char	*str;
// 	int		j;

// 	j = 0;
// 	if (!arg[i + 1])
// 		return (NULL);
// 	arg[i] = remove_quotes(arg[i], arg[i][0]);
// 	file = ft_split(arg[i], c);
// 	if (!file[0])
// 		return (arg[i + 1]);
// 	str = ft_strrchr(arg[i], c) + 1;
// 	while (file[j])
// 		j++;
// 	if (j == 1 && ft_strrchr(arg[i], c) == arg[i])
// 		return (file[0]);
// 	if (!str)
// 	{
// 		free(arg[i]);
// 		arg[i] = file[0];
// 	}
// 	return (file);
// }

void	get_input(int fd, char *stop)
{
	char	*line;

	line = get_next_line(0);
	while (ft_strncmp(line, stop, ft_strlen(stop)))
	{
		write(1, ">", 1);
		if (write(fd, line, ft_strlen(line)) == -1)
			exit_error("Error write", 30);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(fd);
}

void	put_in_file(int type, t_cmd *cmd, char *file)
{
	int	fd;
	char	*temp;

	temp = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	getcwd(temp, MAXPATHLEN);
	temp = ft_strjoin(temp, "/");
	if (type == 1)
		fd = open(ft_strjoin(temp, file), O_CREAT|O_WRONLY|O_TRUNC, 0644);
	else
		fd = open(ft_strjoin(temp, file), O_CREAT|O_WRONLY|O_APPEND, 0644);
	if (fd == -1)
		exit_error("Error open", 44);
	if (dup2(fd, cmd->pipes->out) == -1)
		exit_error("Error dup", 45);
	close(fd);
}

void	get_from_file(t_cmd *cmd, char *file)
{
	int	fd;
	char	*temp;

	temp = ft_calloc(sizeof(char), (MAXPATHLEN + 1));
	getcwd(temp, MAXPATHLEN);
	temp = ft_strjoin(temp, "/");
	fd = open(ft_strjoin(temp, file), O_RDONLY);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, file, ft_strlen(file));
		write(2, ":", 1);
		perror(NULL);
	}
	else if (dup2(fd, cmd->pipes->in) == -1)
		exit_error("Error dup", 45);
	free(temp);
	close(fd);
}

char **remove_one(char **arg, int i)
{
	char **res;
	int	j;
	int k;

	j = 0;
	while (arg[j])
		j++;
	res = ft_calloc(sizeof(char *), j--);
	k = j - 1;
	while (j >= 0)
	{
		if (j != i)
		{
			res[k] = ft_strdup(arg[j]);
			k--;
		}
		free(arg[j]);
		j--;
	}
	free(arg);
	return (res);
}

void	redir(t_cmd	*cmd)
{
	int	i;
	char	*file;
	char	c;

	i = 0;
	while (is_redir((cmd->arg) + i) != -1)
	{
		i = is_redir((cmd->arg) + i) + i;
		file = cmd->arg[i + 1];
		if (redir_type(cmd->arg[i]) == 1 || redir_type(cmd->arg[i]) == 2)
			put_in_file(redir_type(cmd->arg[i]), cmd, file);
		else if (redir_type(cmd->arg[i]) == 3)
			get_from_file(cmd, file);
		cmd->arg = remove_one(cmd->arg, i);
		cmd->arg = remove_one(cmd->arg, i);
	}
}