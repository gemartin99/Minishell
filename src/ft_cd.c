/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:44 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:45 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

void	change_value_pwd(char *s, t_cmd *cmd, int control)
{
	int		i;
	char	*temp;

	i = -1;
	s = actual_path(0);
	while (++i < cmd->env->num_env)
	{
		if (control == 0 && cmd->env->env[i]
			&& !ft_strncmp(cmd->env->env[i], "OLDPWD", 6))
		{
			temp = ft_strjoin("OLDPWD=", s);
			free(cmd->env->env[i]);
			cmd->env->env[i] = temp;
		}
		if (control == 1 && cmd->env->env[i]
			&& !ft_strncmp(cmd->env->env[i], "PWD", 3))
		{
			temp = ft_strjoin("PWD=", s);
			free(cmd->env->env[i]);
			cmd->env->env[i] = temp;
		}
	}
	free(s);
}

//hacer que variable entorno $OLDPWD tenga el valor de la ruta actual 
//antes de hacer algun CD siempre y cuando el CD no sea hacia $OLDPWD
int	ft_cd(t_cmd **cmd)
{
	int		i;
	char	*temp;

	i = 0;
	change_value_pwd(NULL, (*cmd), 0);
	if ((*cmd)->num_arg == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	temp = str_noquotes((*cmd)->arg[0]);
	if (!ft_strncmp(temp, "-", 2))
		chdir(getenv("OLDPWD"));
	else if (chdir(temp) == -1)
		put_error("bash: cd", temp, "No such file or directory");
	else
	{
		free(temp);
		change_value_pwd(NULL, (*cmd), 1);
		return (0);
	}
	free(temp);
	return (1);
}
