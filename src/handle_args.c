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

static int ft_split_args_quote(char *s, int i, t_cmd *cmd, int *pos)
{
	int start;

	start = i;
	i = get_next_quote(i + 1, s, s[i]);
	cmd->arg[*pos] = ft_substr(s, start, i - start + 1);
	if (cmd->arg[*pos] == NULL)
		exit_error("Error malloc", 14);
	(*pos)++;
	return (i);
}

static int ft_split_args(char *s, t_cmd *cmd, int i)
{
	int pos;
	int start;

	start = 0;
	pos = 0;
	printf("%s\n", s);
	while(s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
			i = ft_split_args_quote(s, i, cmd, &pos);
		if ((s[i] == ' ' || s[i] == 34 || s[i] == 39) && s[i + 1] && s[i + 1] != ' ')
			start = i + 1;
		if ((s[i] != ' ' && s[i] != 34 && s[i] != 39) && (s[i + 1] == ' ' || s[i + 1] == '\0'
			|| s[i + 1] == 34 || s[i + 1] == 39))
		{
			printf("start %d i %d\n", start, i);
			cmd->arg[pos] = ft_substr(s, start, i - start + 1);
			//printf("%s\n", cmd->arg[pos]);
			if (cmd->arg[pos] == NULL)
				exit_error("Error malloc", 14);
			pos++;
		}
	}
	cmd->arg[pos] = NULL;
	return (i);
}

static char **ft_get_args(t_msh *msh, char *s, t_cmd *cmd)
{
	int i;

	i = -1;
	cmd->num_arg = ft_count_args(s);
	while (check_null_args(s, 0) == -1)
		s = change_null_args(s, cmd);
	cmd->arg = malloc(sizeof(char *) * (cmd->num_arg + 1));
	if (!cmd->arg)
		exit_error("Error malloc", 13);
	msh->total_chars += ft_split_args(s, cmd, i);
	i = -1;
	printf("%s\n", cmd->arg[0]);
	printf("%s\n", cmd->arg[1]);
	printf("%s\n", cmd->arg[2]);
	printf("%s\n", cmd->arg[3]);
	//while (msh->cmd->arg[++i])
	//	printf("%s\n", cmd->arg[i]);
	return (NULL);	
}

static char *get_comand(t_msh *msh, char *read_line)
{
	int	i;
	int	start;
	char	*str;

	i = 0;
	while (read_line[i] == 32 || (read_line[i] >= 9 && read_line[i] <= 13))
		i++;
	start = i;
	while (read_line[i] && read_line[i] != 32 
			&& !(read_line[i] >= 9 && read_line[i] <= 13))
	{
		if (read_line[i] == 34 || read_line[i] == 39)
			i = get_next_quote(i + 1, read_line, read_line[i]);
		i++;
	}
	str = ft_substr(read_line, start, i);
	i = ft_skip_space(read_line, i);
	msh->total_chars += i;
	return (str);
}

static t_cmd	*add_cmd(t_msh *msh, char *read_line)
{
	t_cmd *temp;

	temp = ft_calloc(sizeof(t_cmd), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	temp->cmd = get_comand(msh, read_line + msh->total_chars);
	temp->num_arg = ft_count_args(read_line + msh->total_chars);
	if (temp->num_arg == 0)
		return (temp);
	temp->arg = ft_get_args(msh, read_line + msh->total_chars, temp);
	temp->next = NULL;
	return (temp);
}

static void	tokenize(t_msh *msh, t_cmd **cmd, char *read_line) //
{
	int i;
	t_cmd	*temp;

	i = 0;
	msh->flags->quote = ft_check_dquote(read_line, 2, 2, msh);
	if (msh->flags->quote == 0)
		return ;
	msh->flags->pipe = ft_count_pipes(read_line);
	*cmd = add_cmd(msh, read_line);
	while (++i <= msh->flags->pipe)
	{
		temp = add_cmd(msh, read_line);
		(ft_last(cmd))->next = temp;
		temp = temp->next;
	}
}

void	recive_arguments(t_msh *msh)
{
	char	*read_line;
	
	while (1)
	{
		read_line = readline( BLUE_T "Mi" WHITE_T "ni" YELLOW_T "s"
				WHITE_T "he" BLUE_T "ll" "🇦🇷 🧉->" RESET_COLOR);
		if (!read_line)
			exit_error("exit", 0);
		if (read_line[0] == '\0')
			printf("");
		else
		{
			msh->total_chars = 0;
			add_history(read_line);
			tokenize(msh, &msh->cmd, read_line);
			if (msh->flags->quote != 0)
				cmd_type(msh);
		}
	}
}
