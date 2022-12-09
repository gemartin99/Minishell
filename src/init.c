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

static void	create_env(t_env *env, char **ev) // incializar env
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
	i--;
	while (i >= 0)
	{
		temp[i] = ft_strdup(ev[i]);
		if (ft_strncmp(temp[i], "PATH=", 5) == 0)
			env->path = ft_substr(temp[i], 5, ft_strlen(temp[i]) - 5);
		i--;
	}
	if (!env->path)
		env->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env->env = temp;
}

t_msh	*init(char **env) //init estructura general
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
