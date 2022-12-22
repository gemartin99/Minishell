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

static int	wrong_exp(char c)
{
	if (c == '?' || c == '!' || c == '.'
		|| c == '+' || c == '}' || c == '{' || c == '-' || c == 92
		|| c == '[' || c == ']' || c == '@' || c == '*' || c == '#'
		|| c == '^' || c == '~')
	{
		return (1);
	}
	return (0);
}

char	*ft_quit_last_char(char *s, int i)
{
	char	*res;
	int		j;

	j = -1;
	while (s[i])
	{
		if (wrong_exp(s[i]) == 0 && s[i + 1]
			&& s[i + 1] == '+' && s[i + 2] && s[i + 2] == '=')
			break ;
		i++;
	}
	res = malloc(sizeof(char) * ft_strlen(s));
	if (!res)
		exit_error("Error malloc", 22);
	while (++j <= i)
		res[j] = s[j];
	i++;
	while (s[++i])
	{
		res[j] = s[i];
		j++;
	}
	res[j] = '\0';
	free(s);
	return (res);
}

//funcion que controla si hay caracteres o combinaciones
//de caracteres que provoquen que no se pueda realizar el export
int	parse_equal(char *s, int i)
{
	int	correct;

	correct = 0;
	while (s[i])
	{
		if (wrong_exp(s[i]) == 0 && s[i + 1] && s[i + 1] == '+'
			&& s[i + 2] && s[i + 2] == '=')
			return (-2);
		else if (s[i] == '!' && s[i + 1] && s[i + 1] != '=')
		{
			put_error("bash", s, "event not found");
			return (-1);
		}
		else if (wrong_exp(s[i]) == 1 || ft_isdigit(s[0]) == 1 || s[0] == 61)
		{
			put_error("bash: export", s, "not a valid identifier");
			return (-1);
		}
		if (s[i] == '=')
			correct++;
		i++;
	}
	if (correct == 0 || i == 1 || i == correct)
		return (-1);
	return (0);
}

void	del_exist_variable(char *full_var, t_cmd *cmd, int i)
{
	char	*var;
	int		len;
	int		j;

	len = 0;
	if (full_var[0] == '=')
		return ;
	while (full_var[len] && full_var[len] != '=')
		len++;
	while (i < cmd->env->num_env)
	{
		while (cmd->env->env[i] == NULL && i < cmd->env->num_env)
			i++;
		if (i >= cmd->env->num_env)
			break ;
		var = cmd->env->env[i];
		j = -1;
		while (++j != len)
			if (full_var[j] != var[j])
				break ;
		if (j == len)
			cmd->env->env[i] = NULL;
		i++;
	}
}

//⚠️implementar valor variables de otras variables con $ , pero sobretodo
//el que una nueva variable tenga el valor de 2 o mas variables de entorno⚠️
int	export_parse(t_cmd *cmd, char *array, int j, int control)
{
	int	i;

	i = -1;
	while (cmd->arg[++i])
	{
		del_exist_variable(cmd->arg[i], cmd, 0);
		j = parse_equal(cmd->arg[i], 0);
		if (j == -2)
		{
			cmd->arg[i] = ft_quit_last_char(cmd->arg[i], 0);
			ft_export(&cmd);
			return (-2);
		}
		else if (j == -1)
		{
			array[i] = '0';
			control++;
		}
		else
			array[i] = '1';
	}
	array[i] = '\0';
	if (control != 0)
		return (-1);
	return (0);
}

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
