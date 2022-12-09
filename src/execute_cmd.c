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
	int	i;
	char	*temp;
	
	i = 0;
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
			temp[i] = ft_tolower(str[i]);
		i++;
	}
	return (temp);
}

void	cmd_type(t_msh *msh)
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
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "pwd", 4))
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "export", 7))
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "unset", 6))
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "env", 4))
			printf("%s\n", temp_cmd);
		else if (!ft_strncmp(temp_cmd, "exit", 5))
			printf("%s\n", temp_cmd);
		else
			printf("%s\n", temp_cmd);
		temp = temp->next;
		free(temp_cmd);
	}
}
