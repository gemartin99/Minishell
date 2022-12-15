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

//IMPORTANTE cuando esten las redirecciones hechas añadir el mensaje de error: No such file or directory. Ej bash: <to_file_no_exist

#include "../inc/minishell.h"

char *value_dolar_path(char *s) //funcion que muestra el valor de la variable path pero se ira acortando cada vez que se intente ejecutar algo en una de las rutas
{
	int i;
	char *res;

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

static int ft_count_env(char **arg, int len) //funcion para contar todas las variables de entorno que no sean nulas.
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i + j < len)
	{
		if (arg[i + j])
			i++;
		else
			j++;
	}
	return (i - j);
}

char **convert_to_env(char **arg, int len) //funcion que retorna una variable que guarde todas las variables de entorno actuales.
{
	int i;
	int j;
	char **res;

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
	char **res;
	int i;

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
			res[i] = str_noquotes(cmd->arg[i - 1]);
			res[i] = remove_quotes(res[i], ';');
			i--;
		}
	}
	res[0] = cmd->cmd;
	return (res);
}

int ft_try_to_exec(t_cmd *cmd) //funcion para intentar hacer execv de lo que me manden
{
	//CHECKEAR SI ME MANDAN PATH ABSOLUTA Y SI LO HACEN EJECUTAR ESO DIRECTAMENTE

	char *absolute_path;
	char *search_path;
	t_env	*env;

	env = cmd->env;
	cmd->cmd = ft_strtrim(str_noquotes(cmd->cmd), " ");
	absolute_path = value_dolar_path(env->path);
	while (absolute_path)
	{
		search_path = ft_strjoin(absolute_path, cmd->cmd);
		if (access(search_path, F_OK) != -1)
		{
			if (access(search_path, X_OK) != -1)
				execve(search_path, arg_with_command(cmd), convert_to_env(env->env, env->num_env)); //poner variables de entorno propias para que los comandos que necesiten las env las puedan utilizar
			printf("bash: %s: Permision denired\n", cmd->cmd);
		}
		free(search_path);
		env->path = ft_strchr(env->path, ':');
		if (env->path)
			env->path++;
		absolute_path = value_dolar_path(env->path);
	}
	printf("bash: %s: comand not found\n", str_noquotes(cmd->cmd));
	return (0);
}
