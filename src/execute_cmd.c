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

static char	*str_tolower(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = 0;
	j = 0;
	doubles = 1;
	simples = 1;
	if (str[i] == 34 || str[i] == 39)
	{
		str = remove_quotes(str, str[i]);
		doubles = -1;
		simples = -1;
	}
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[i])
	{
		while (str[i] == 34 && simples != -1 && i++)
				doubles *= -1;
		while (str[i] == 39 && doubles != -1 && i++)
			simples *= -1;
		temp[j] = ft_tolower(str[i]);
		i++;
		j++;
	}
	return (temp);
}

void	cmd_type(t_msh *msh, char *read_line)
{
	t_cmd	*temp;
	char	*temp_cmd;

	temp = msh->cmd;
	while (temp)
	{
		temp_cmd = str_tolower(temp->cmd);
		if (!ft_strncmp(temp_cmd, "echo", 5))
			ft_echo(&temp);
		else if (!ft_strncmp(temp_cmd, "cd", 3))
			ft_cd(&temp, read_line);
		else if (!ft_strncmp(temp_cmd, "pwd", 4))
			ft_pwd(0);
		else if (!ft_strncmp(temp_cmd, "export", 7))
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "unset", 6))
			ft_unset(&temp);
		else if (!ft_strncmp(temp_cmd, "env", 4))
			ft_env(msh->env);
		else if (!ft_strncmp(temp_cmd, "exit", 5))
			printf("%s\n", temp_cmd);
		else
			printf("%s\n", temp_cmd);
		temp = temp->next;
		free(temp_cmd);
	}
}
