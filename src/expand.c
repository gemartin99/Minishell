/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:12 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:25:14 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//funcion para buscar el siguiente caracter que no este entre comillas
int	search_next_char(char *s, char c, int i)
{
	while (s[++i])
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

//funcion para añadir el valor de la variable
//de entorno a nuestra variable result
static char	*ft_add_var_value(char *s1)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	result = malloc(sizeof(char) * ft_strlen(s1) - i + 1);
	if (!result)
		exit_error("Error malloc", 17);
	while (s1[++j])
		result[j - 1] = s1[i + j];
	result[j] = '\0';
	return (result);
}

char	*ft_craft_result(char *line_final, char *line, char *var, int c)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = search_next_char(line, '$', -1);
	if ((size_t)k == ft_strlen(line))
		return (line);
	while (++i < k)
		line_final[i] = line[i];
	while (var[++j])
		line_final[i + j] = var[j];
	while (line[i + c])
	{
		line_final[i + j] = line[i + c];
		i++;
	}
	line_final[i + j] = '\0';
	return (line_final);
}

//funcion que cambia el valor de la linea y sustituye el $var 
//por el valor de la variable si esa variable existe
char	*change_line_value(char *line, char *var)
{
	int		i;
	int		j;
	char	*line_final;
	int		c;

	j = 0;
	i = search_next_char(line, '$', -1);
	c = i;
	while (line[i + j] && line[i + j] != ' '
		&& line[i + j] != 34 && line[i + j] != 39)
			j++;
	while (line[i + j])
		i++;
	line_final = malloc(sizeof(char) * i + ft_strlen(var));
	if (!line_final)
		exit_error("Error malloc", 18);
	line_final = ft_craft_result(line_final, line, var, j);
	return (line_final);
}

//funcion recursiva para ir quitando todos los digitos y dolares sobrantes. 
//ej: $1aaa $2bb. Quedaria asi aaa bb
char	*quit_dollar_and_digit(char *s, int i, int j)
{
	char	*res;

	while (s[++i])
	{
		if (s[i] && s[i] == '$' && s[i + 1]
			&& ft_isdigit_special(s[i + 1]) == 1)
		{
			j = -1;
			res = malloc(sizeof(char) * ft_strlen(s) - 1);
			if (!res)
				exit_error("Error malloc", 15);
			while (++j < i)
				res[j] = s[j];
			i++;
			while (s[++i])
			{
				res[j] = s[i];
				j++;
			}
			res[j] = '\0';
			free(s);
			s = quit_dollar_and_digit(res, -1, -1);
		}
	}
	return (s);
}

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

//funcion que crea una variable con el nombre que tiene el argumento que me
//manden cn $ para luego comprarlo con las variables de entorno
char	*ft_name_var(char *line)
{
	int		j;
	int		i;
	char	*result;

	i = get_next_quote(0, line, '$') + 1;
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && check_special_char(line[i + j]) == 0)
		j++;
	result = ft_calloc(sizeof(char), j + 1);
	if (!result)
		exit_error("Error malloc", 16);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && check_special_char(line[i + j]) == 0)
	{
		result[j] = line[i + j];
		j++;
	}
	return (result);
}

//funcion que retorna el resto de una variable si hay caracteres especiales. 
//Ej: echo "$USER@hola" esta funcion retornara @hola
char	*ft_split_var(char *line, int i, t_cmd *cmd)
{
	int		j;
	char	*res;

	cmd->flags->dollar_special = 1;
	j = i;
	while (line[i])
		i++;
	res = malloc(sizeof(char) * i - j + 1);
	if (!res)
		exit_error("Error malloc", 17);
	i = 0;
	while (line[j])
	{
		res[i] = line[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

//funcion para detectar y cambiar el valor a la linea y que si hay un caracter
// especial despues de $var se concatene. Ej: $USER/aaa 
char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder)
{
	char	*name_var;
	int		i;
	char	*result;

	if (ft_strnstr(line, "$?", ft_strlen(line)) != 0)
		line = ft_replace_value(line);
	name_var = ft_name_var(line);
	i = search_next_char(line, '$', -1);
	while (line[++i] && line[i] != ' ')
	{
		if ((check_special_char(line[i]) == -1 && line[i] != '$') || (line[i] == '$' && i == search_next_char(line, '$', search_next_char(line, '$', -1) + 1)))
		{
			*var_reminder = ft_split_var(line, i, cmd);
			break ;
		}
	}
	if (!name_var)
		return (NULL);
	if (!name_var[0])
		return (line);
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

char	*change_dolar_x_var(t_cmd *cmd, char *s)
{
	char	*var_reminder;

	if (check_dolar_and_digit(s) == 0)
		s = quit_dollar_and_digit(s, -1, -1);
	if (check_dolar(s) == 0)
		return (s);
	cmd->flags->dollar_special = 0;
	s = ft_change_var(cmd, s, &var_reminder);
	if (check_dolar(s) == 1)
		s = change_dolar_x_var(cmd, s);
	if (cmd->flags->dollar_special == 1)
	{
		s = ft_strjoin_special(s, var_reminder, 0, 0);
		cmd->flags->dollar_special = 0;
	}
	if (check_dolar(s) == 1)
		s = change_dolar_x_var(cmd, s);
	return (s);
}

void	expand(t_cmd **cmd)
{
	int	i;

	i = -1;
	if (check_dolar((*cmd)->cmd) == 1)
		(*cmd)->cmd = change_dolar_x_var((*cmd), (*cmd)->cmd);
	if (!(*cmd)->arg)
		return ;
	while ((*cmd)->arg[++i])
	{
		if (check_dolar((*cmd)->arg[i]) == 1)
			(*cmd)->arg[i] = change_dolar_x_var((*cmd), (*cmd)->arg[i]);
	}
}
