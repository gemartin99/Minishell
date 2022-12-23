/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:27:48 by smiro             #+#    #+#             */
/*   Updated: 2022/12/22 11:27:51 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

static char	*ft_quit_last_char(char *s, int i)
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
static int	parse_equal(char *s, int i)
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
		return (-3);
	return (0);
}

static void	del_exist_variable(char *full_var, t_cmd *cmd, int i)
{
	char	*var;
	int		len;

	len = 0;
	if (full_var[0] == '=')
		return ;
	while (i < cmd->env->num_env)
	{
		while (cmd->env->env[i] == NULL && i < cmd->env->num_env)
			i++;
		if (i >= cmd->env->num_env)
			break ;
		var = cmd->env->env[i];
		len = get_next_quote(0, var, '=');
		if (!ft_strncmp(full_var, var, len + 1))
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
			control = -1;
		}
		else if (j == -3)
			array[i] = '0';
		else
			array[i] = '1';
	}
	array[i] = '\0';
	return (control);
}
