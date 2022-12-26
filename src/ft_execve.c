/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:55:09 by smiro             #+#    #+#             */
/*   Updated: 2022/12/12 12:55:13 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

//funcion que muestra el valor de la variable path pero se 
//ira acortando cada vez que se intente ejecutar algo en una de las rutas
char	*value_dolar_path(char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (!s || !s[i])
		return (NULL);
	while (s[i] && s[i] != ':')
		i++;
	res = malloc(sizeof(char) * i + 2);
	if (!res)
		exit_error("Error malloc", 25);
	i = 0;
	while (*s && *s != ':')
	{
		res[i] = *s;
		s++;
		i++;
	}
	res[i] = '/';
	res[i + 1] = '\0';
	return (res);
}

//funcion que retorna una variable que 
//guarde todas las variables de entorno actuales
char	**convert_to_env(char **arg, int len)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * ft_count_env(arg, len) + 1);
	if (!res)
		exit_error("Error malloc", 27);
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (arg[i])
		{
			res[j] = ft_strdup(arg[i]);
			if (!res[j])
				exit_error("Error malloc", 35);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}

char	**arg_with_command(t_cmd *cmd)
{
	char	**res;
	int		i;

	i = 0;
	if (!cmd->arg)
	{
		res = ft_calloc(sizeof(char *), 2);
		if (!res)
			exit_error("Error malloc", 36);
	}
	else
	{
		while (cmd->arg[i])
			i++;
		res = ft_calloc(sizeof(char *), i + 2);
		if (!res)
			exit_error("Error malloc", 37);
		while (i > 0)
		{
			res[i] = str_noquotes(remove_quotes(cmd->arg[i - 1], ';'));
			i--;
		}
	}
	res[0] = cmd->cmd;
	return (res);
}

int	check_access(char *path, t_cmd *cmd, t_env *env)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, X_OK) != -1)
			execve(path, arg_with_command(cmd),
				convert_to_env(env->env, env->num_env));
		put_error("bash", cmd->cmd, "Permision denied");
		return (126);
	}
	return (0);
}

//funcion para intentar hacer execv de lo que me manden
int	ft_try_to_exec(t_cmd *cmd)
{
	char	*absolute_path;
	char	*search_path;

	cmd->cmd = ft_strtrim(str_noquotes((cmd->cmd)), " ");
	absolute_path = value_dolar_path(cmd->env->path);
	if (cmd->cmd[0] == '.' || cmd->cmd[0] == '/')
	{
		if (!check_access(cmd->cmd, cmd, cmd->env))
			put_error("bash", cmd->cmd, "No such file or directory");
		return (127);
	}
	while (absolute_path && cmd->cmd[0])
	{
		search_path = ft_strjoin(absolute_path, cmd->cmd);
		if (check_access(search_path, cmd, cmd->env))
			return (1);
		free(search_path);
		cmd->env->path = ft_strchr(cmd->env->path, ':');
		if (cmd->env->path)
			cmd->env->path++;
		absolute_path = value_dolar_path(cmd->env->path);
	}
	put_error("bash", cmd->cmd, "comand not found");
	return (127);
}
