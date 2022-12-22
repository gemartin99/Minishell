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

static int	ft_split_args(char *s, char **arg)
{
	int	pos;
	int	start;
	int	i;

	start = 0;
	pos = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			&& s[i + 1] && s[i + 1] != ' ')
			start = i + 1;
		if (s[i] == 34 || s[i] == 39)
			i = get_next_quote(i + 1, s, s[i]);
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13)
			&& (s[i + 1] == ' ' || s[i + 1] == '\0'))
		{
			arg[pos] = ft_substr(s, start, i - start + 1);
			if (arg[pos] == NULL)
				exit_error("Error malloc", 14);
			pos++;
		}
	}
	arg[pos] = NULL;
	return (i);
}

static char	**ft_get_args(t_msh *msh, char *s, t_cmd *cmd)
{
	char	**arg;

	while (check_null_args(s) == -1)
		s = change_null_args(s, cmd);
	arg = malloc(sizeof(char *) * (cmd->num_arg + 1));
	if (!arg)
		exit_error("Error malloc", 13);
	msh->total_chars += ft_split_args(s, arg);
	return (arg);
}

static char	*get_comand(t_msh *msh, char *read_line)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	while (read_line[i] == 32 || (read_line[i] >= 9 && read_line[i] <= 13))
		i++;
	start = i;
	while (read_line[i] && read_line[i] != 32
		&& !(read_line[i] >= 9 && read_line[i] <= 13)
		&& !isdifoperator(read_line[i]))
	{
		if (read_line[i] == 34 || read_line[i] == 39)
			i = get_next_quote(i + 1, read_line, read_line[i]);
		i++;
	}
	if (i)
		str = ft_substr(read_line, start, i);
	else
		str = ft_strdup("CD");
	msh->total_chars += i;
	return (str);
}

static t_cmd	*add_cmd(t_msh *msh, char *read_line)
{
	t_cmd	*temp;

	temp = ft_calloc(sizeof(t_cmd), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	temp->cmd = get_comand(msh, read_line + msh->total_chars);
	temp->num_arg = ft_count_args(read_line + msh->total_chars);
	temp->next = NULL;
	temp->flags = msh->flags;
	temp->env = msh->env;
	if (temp->num_arg == 0)
		return (temp);
	temp->arg = ft_get_args(msh, read_line + msh->total_chars, temp);
	return (temp);
}

static int	tokenize(t_msh *msh, t_cmd **cmd, char *read_line)
{
	int		i;
	t_cmd	*temp;
	char	**lines;

	i = 0;
	lines = NULL;
	if (start_line(&msh, read_line, &lines))
		return (0);
	*cmd = add_cmd(msh, lines[0]);
	expand(cmd);
	while (++i <= msh->flags->pipe)
	{
		msh->total_chars = 0;
		temp = add_cmd(msh, lines[i]);
		expand(&temp);
		(ft_last(cmd))->next = temp;
		temp = temp->next;
	}
	while (i--)
		free(lines[i]);
	free(lines);
	free(read_line);
	return (1);
}

void	recive_arguments(t_msh *msh)
{
	char	*read_line;

	while (1)
	{
		read_line = readline(BLUE_T "Mi" WHITE_T "ni" YELLOW_T "s"
				WHITE_T "he" BLUE_T "ll" "🇦🇷 🧉->" RESET_COLOR);
		if (!read_line)
			exit_error("exit", 0);
		if (read_line[0] == '\0')
			printf("");
		else
		{
			msh->total_chars = 0;
			add_history(read_line);
			if (tokenize(msh, &msh->cmd, read_line) && msh->flags->quote != 0)
			{
				if (check_nonpipables(msh->cmd, str_noquotes(msh->cmd->cmd)))
					execute_nonpipe(msh->cmd, str_noquotes(msh->cmd->cmd));
				else
					execute_cmd(&(msh->cmd), init_pipes());
			}
		}
	}
}
