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
#include "../inc/libft/libft.h"

//segunda parte de funcion que calcula cuantas variables nuevas hay para
//crear la reserva de memoria debida para luego poder hacer el realloc
void	add_new_vars2(t_cmd **cmd, char *binary_array, int i, char **aux)
{
	int	j;

	j = -1;
	while (binary_array[++j])
	{
		if (binary_array[j] == '1')
		{
			aux[i] = ft_strdup((*cmd)->arg[j]);
			i++;
		}
	}
	free(binary_array);
	(*cmd)->env->env = aux;
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
		if (binary_array[i] == '1')
			new_envs++;
	aux = ft_calloc(sizeof(char *), (cmd->env->num_env + new_envs));
	if (!aux)
		exit_error("Error malloc", 24);
	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (!cmd->env->env[i])
			aux[i] = NULL;
		else
			aux[i] = ft_strdup(cmd->env->env[i]);
		free(cmd->env->env[i]);
	}
	free(cmd->env->env);
	cmd->env->num_env = cmd->env->num_env + new_envs;
	add_new_vars2(&cmd, binary_array, i, aux);
	return (0);
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	*binary_array;
	char	*temp;

	i = -1;
	if (!(*cmd)->arg || !(*cmd)->arg[0])
	{
		print_export_var((*cmd));
		return (0);
	}
	while ((*cmd)->arg[++i] && i <= (*cmd)->num_arg)
	{
		temp = str_noquotes((*cmd)->arg[i]);
		free((*cmd)->arg[i]);
		(*cmd)->arg[i] = temp;
	}
	binary_array = malloc(sizeof(char) * (*cmd)->num_arg + 1);
	if (!binary_array)
		exit_error("Error malloc", 21);
	i = 0;
	if (export_parse((*cmd), binary_array, 0, 0) == -1)
		i = 1;
	add_new_vars1((*cmd), binary_array);
	return (i);
}
