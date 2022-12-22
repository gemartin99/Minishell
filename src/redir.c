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

static char	**get_filename(char **arg, int j, char c, int k);

static char	**remove_one(char **arg, int i)
{
	char	**res;
	int		j;
	int		k;

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

static char	**add_one(char **arg, char *new, int j)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (arg[i++])
		;
	res = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (arg[k])
	{
		res[i] = ft_strdup(arg[k]);
		free(arg[k]);
		i++;
		k++;
		if (k == j)
			res[i++] = new;
	}
	free(arg);
	return (res);
}

static char	**keep_arg(char **arg, int j, char c)
{
	char	*temp;

	arg = add_one(arg, ft_substr(arg[j],
				0, get_next_diff(0, arg[j])), j + 1);
	temp = ft_strdup(ft_strchr(arg[j], c));
	free(arg[j]);
	arg[j] = temp;
	return (get_filename(arg, j, c, 2));
}

static char	**get_filename(char **arg, int j, char c, int k)
{
	int		i;

	i = 0;
	while (arg[j][i] == c)
		i++;
	if (!arg[j][i])
		return (arg);
	if (i == 0)
		return (keep_arg(arg, j, c));
	arg = add_one(arg, ft_substr(arg[j], 0, i), j + k++);
	arg = add_one(arg, ft_substr(arg[j], i,
				get_next_diff(i, arg[j]) - i), j + k++);
	i = get_next_diff(i, arg[j]);
	if (arg[j][i])
		arg = add_one(arg, ft_substr
				(arg[j], i, ft_strlen(arg[j]) - i), j + k++);
	arg = remove_one(arg, j);
	return (arg);
}

void	redir(t_cmd	*cmd)
{
	int		i;
	char	*file;

	i = 0;
	while (is_redir((cmd->arg) + i) != -1)
	{
		i = is_redir((cmd->arg) + i) + i;
		cmd->arg = get_filename(cmd->arg, i,
				operator_char(redir_type(cmd->arg[i])), 1);
		if (!redir_type(cmd->arg[i]))
			i++;
		if (redir_type(cmd->arg[i + 1]))
			cmd->arg = get_filename(cmd->arg, i + 1,
					operator_char(redir_type(cmd->arg[i + 1])), 1);
		file = str_noquotes(cmd->arg[i + 1]);
		if (redir_type(cmd->arg[i]) == 1 || redir_type(cmd->arg[i]) == 2)
			put_in_file(redir_type(cmd->arg[i]), cmd, file);
		else if (redir_type(cmd->arg[i]) == 3 && get_from_file(cmd, file))
			return ;
		else if (redir_type(cmd->arg[i]) == 4)
			get_input(cmd, file);
		cmd->arg = remove_one(cmd->arg, i);
		cmd->arg = remove_one(cmd->arg, i);
	}
}
