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

//funcion para añadir el valor de la variable
//de entorno a nuestra variable result
char	*ft_add_var_value(char *s1)
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

	printf("1\n");
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
	printf("2\n");
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
