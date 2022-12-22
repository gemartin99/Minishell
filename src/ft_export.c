/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:31 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:33 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//segunda parte de funcion que calcula cuantas variables nuevas hay para
//crear la reserva de memoria debida para luego poder hacer el realloc
void	add_new_vars2(t_cmd *cmd, char *binary_array, int i, char **aux)
{
	int	j;

	j = -1;
	while (binary_array[++j])
	{
		if (binary_array[j] == '1')
		{
			aux[i] = cmd->arg[j];
			i++;
		}
	}
	cmd->env->env = (char **)malloc(sizeof(char *) * cmd->env->num_env);
	if (cmd->env->env == NULL)
		exit_error("Error malloc", 23);
	i = -1;
	while (++i < cmd->env->num_env)
		cmd->env->env[i] = aux[i];
}

//primera parte de funcion que calcula cuantas variables nuevas
//hay para crear la reserva de memoria debida para luego poder hacer el realloc
int	add_new_vars1(t_cmd *cmd, char *binary_array)
{
	char	**aux;
	int		i;
	int		new_envs;

	i = -1;
	new_envs = 0;
	while (binary_array[++i])
	{
		if (binary_array[i] == '1')
			new_envs++;
	}
	aux = malloc(sizeof(char *) * (cmd->env->num_env + new_envs));
	if (!aux)
		exit_error("Error malloc", 24);
	i = 0;
	while (i < cmd->env->num_env)
	{
		aux[i] = cmd->env->env[i];
		i++;
	}
	free(cmd->env->env);
	cmd->env->num_env = cmd->env->num_env + new_envs;
	add_new_vars2(cmd, binary_array, i, aux);
	return (0);
}

//funcion para añadir el valor de la variable
//de entorno a nuestra variable result
char	*add_var_value(char *s1)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	result = malloc(sizeof(char) * ft_strlen(s1) - i);
	if (!result)
		exit_error("Error malloc", 25);
	while (s1[++j])
		result[j - 1] = s1[i + j];
	result[j] = '\0';
	return (result);
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	*binary_array;

	i = -1;
	if (!(*cmd)->arg || !(*cmd)->arg[0])
	{
		print_export_var((*cmd));
		return (0);
	}
	while ((*cmd)->arg[++i] && i <= (*cmd)->num_arg)
		(*cmd)->arg[i] = str_noquotes((*cmd)->arg[i]);
	binary_array = malloc(sizeof(char) * (*cmd)->num_arg + 1);
	if (!binary_array)
		exit_error("Error malloc", 21);
	i = 0;
	if (export_parse((*cmd), binary_array, 0, 0) == -1)
		i = 1;
	add_new_vars1((*cmd), binary_array);
	return (i);
}
