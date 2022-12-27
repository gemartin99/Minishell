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
#include "../inc/libft/libft.h"

//funcion para buscar la primera variable de entorno (alfabeticamente)
char	*search_lowest(char **env2)
{
	int		i;
	int		j;
	char	*res;

	j = 0;
	i = 0;
	res = env2[0];
	if (!env2[i + 1])
		env2[0] = NULL;
	while (env2[i])
	{
		if (ft_strncmp(res, env2[i], ft_strlen(res)) > 0)
		{
			res = env2[i];
			j = i;
		}
		i++;
	}
	env2[j] = env2[i - 1];
	env2[i - 1] = NULL;
	return (res);
}

//funcion que retorna una variable que 
//guarde todas las variables de entorno actuales
char	**convert_to_env(char **arg, int len)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * len + 1);
	if (!res)
		exit_error("Error malloc", 27);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (arg[j + i] && arg[j + i][0])
		{
			res[j] = ft_strdup(arg[i + j]);
			if (!res[j])
				exit_error("Error malloc", 35);
			j++;
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_ord_env(char **res, t_cmd *cmd)
{
	int		i;
	char	**env2;
	int		num_env;

	num_env = ft_count_env(cmd->env->env, cmd->env->num_env);
	env2 = convert_to_env(cmd->env->env, num_env);
	i = 0;
	while (num_env - i)
		res[i++] = search_lowest(env2);
	free(env2);
	return (res);
}

char	*ft_add_quotes(char *s)
{
	int		i;
	char	*res;

	i = -1;
	res = ft_calloc(sizeof(char), ft_strlen(s) + 3);
	if (!res)
		exit_error("Error malloc", 51);
	while (s[++i])
	{
		res[i] = s[i];
		if (s[i] == '=')
		{
			res[i + 1] = 34;
			break ;
		}
	}
	while (s[++i])
		res[i + 1] = s[i];
	res[i + 1] = 34;
	res[i + 2] = '\0';
	free(s);
	return (res);
}

void	print_export_var(t_cmd *cmd)
{
	int		i;
	char	**res;

	i = 0;
	res = ft_calloc(sizeof(char *), cmd->env->num_env + 1);
	if (!res)
		exit_error("Error malloc", 28);
	res = ft_ord_env(res, cmd);
	while (res[i])
	{
		if (res[i] != NULL)
		{
			res[i] = ft_add_quotes(res[i]);
			printf("declare -x %s\n", res[i]);
		}
		free(res[i]);
		i++;
	}
	free(res);
}
