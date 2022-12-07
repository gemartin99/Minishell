/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 02:31:14 by smiro             #+#    #+#             */
/*   Updated: 2022/12/07 02:31:17 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	create_env(t_cmd *cmd, char **env) // incializar env
{
	char **temp;
	int	i;
	
	i = 0;
	while (env[i])
		i++;
	cmd->num_env = i;
	temp = ft_calloc(i, sizeof(char *));
	if (!temp)
		exit_error("Error malloc", 3);
	i--;
	while (i >= 0)
	{
		temp[i] = ft_strdup(env[i]);
		if (ft_strncmp(temp[i], "PATH=", 5) == 0)
			cmd->path = ft_substr(temp[i], 5, ft_strlen(temp[i]) - 5);
		i--;
	}
	if (!cmd->path)
		cmd->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

t_msh	*init(char **env) //init estructura general
{
	t_msh	*msh;
	
	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		exit_error("Error malloc", 1);
	msh->bash_lvl = 2;
	msh->cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!msh->cmd)
		exit_error("Error malloc", 2);
	create_env(msh->cmd, env);
	msh->flags = ft_calloc(sizeof(t_flags), 1);
	if (!msh->flags)
		exit_error("Error malloc", 4);
	msh->tokens = ft_calloc(sizeof(t_token), 1);
	if (!msh->tokens)
		exit_error("Error malloc", 8);
	return (msh);
}
