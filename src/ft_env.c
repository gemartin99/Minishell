/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:24:37 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:24:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg)
	{
		put_error("env", remove_quotes(cmd->arg[0], ';'), "No such file or directory");
		return (127);
	}
	while (i < cmd->env->num_env)
	{
		if (cmd->env->env[i] != NULL)
			printf("%s\n", cmd->env->env[i]);
		i++;
	}
	return (0);
}
