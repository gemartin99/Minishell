/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:12 by smiro             #+#    #+#             */
/*   Updated: 2022/12/22 11:45:06 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
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

	if (ft_strnstr(line, "$?", ft_strlen(line)) != 0)
		line = ft_replace_value(line);
	name_var = ft_name_var(line);
	i = search_next_char(line, '$', -1);
	while (line[++i] && line[i] != ' ')
	{
		if ((check_special_char(line[i]) == -1
				&& line[i] != '$') || (line[i] == '$'
				&& i == search_next_char(line, '$',
					search_next_char(line, '$', -1) + 1)))
		{
			*var_reminder = ft_split_var(line, i, cmd);
			break ;
		}
	}
	if (!name_var)
		return (NULL);
	if (!name_var[0])
		return (line);
	return (cmp_name_var(cmd, line, name_var));
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
