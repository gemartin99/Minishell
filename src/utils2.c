/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:18:59 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 05:19:00 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/libft/libft.h"

//funcion para detectar si hay un digito despues de un dolar 
//para posteriormente quitarlo, tanto el dolar como el numero
int	check_dolar_and_digit(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '$')
		;
	if (s[i] && s[i] == '$' && s[i + 1] && ft_isdigit_special(s[i + 1]) == 1)
		return (0);
	else
		return (1);
}

//funcion para buscar el siguiente caracter que no este entre comillas
int	search_next_char(char *s, char c, int i)
{
	while (s[++i] && s[i + 1])
	{
		if (s[i] == 34)
		{
			while (s[++i] != 34)
				if (s[i] == '$')
					return (i);
		}
		if (s[i] == 39)
		{
			i++;
			i = get_next_quote(i, s, 39);
		}
		if (s[i] == c)
			return (i);
	}
	return (0);
}

//funcion que checkea si es un numero o caracter especial
int	ft_isdigit_special(int i)
{
	if (i == '*' || i == '@' || i == 92)
		return (1);
	else if (i < 48 || i > 57)
		return (0);
	return (1);
}

//funcion para checkear si despues de la variable
//hay algunos caracter especial ya que cambia la interpretacion de la var
int	check_special_char(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$')
		return (-1);
	return (0);
}

char	*cmp_name_var(t_cmd *cmd, char *line, char *name_var)
{
	int		i;
	char	*result;

	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (var_strcmp(name_var, cmd->env->env[i]) == 0)
		{
			free(name_var);
			result = ft_add_var_value(cmd->env->env[i]);
			return (change_line_value(line, result));
		}
		else if (i + 1 == cmd->env->num_env)
			return (change_line_value(line, ft_strdup("")));
	}
	return (0);
}
