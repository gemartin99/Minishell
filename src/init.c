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
#include "../inc/libft/libft.h"

// incializar env
static void	create_env(t_env *env, char **ev)
{
	char	**temp;
	int		i;

	i = 0;
	while (ev[i])
		i++;
	env->num_env = i;
	temp = ft_calloc(i, sizeof(char *));
	if (!temp)
		exit_error("Error malloc", 3);
	while (--i >= 0)
	{
		temp[i] = ft_strdup(ev[i]);
		if (ft_strncmp(temp[i], "PATH=", 5) == 0)
			env->path = ft_substr(temp[i], 5, ft_strlen(temp[i]) - 5);
		if (ft_strncmp(temp[i], "SHLVL=", 6) == 0)
		{	
			free(temp[i]);
			temp[i] = ft_strjoin("SHLVL=", ft_itoa
					(ft_atoi(ft_strchr(ev[i], '=') + 1) + 1));
		}
	}
	if (!env->path)
		env->path = ft_strdup("./");
	env->env = temp;
}

//init estructura general
t_msh	*init(char **env)
{
	t_msh	*msh;

	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		exit_error("Error malloc", 1);
	msh->bash_lvl = 2;
	msh->env = ft_calloc(sizeof(t_cmd), 1);
	if (!msh->env)
		exit_error("Error malloc", 2);
	create_env(msh->env, env);
	msh->flags = ft_calloc(sizeof(t_flags), 1);
	if (!msh->flags)
		exit_error("Error malloc", 4);
	return (msh);
}

t_cmd	*ft_last(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
