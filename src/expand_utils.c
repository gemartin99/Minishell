/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:26:30 by smiro             #+#    #+#             */
/*   Updated: 2022/12/10 00:26:31 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	var_strcmp(char *s1, char *s2) //, t_msh *d) //funcion strcmp modificada para variables de entorno
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != i)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit_special(int i) //funcion que checkea si es un numero o caracter especial
{
	if (i == '*' || i == '@' || i == 92)
		return (1);
	else if (i < 48 || i > 57)
		return (0);
	return (1);
}

int	check_special_char(char c) //funcion para checkear si despues de la variable hay algunos caracter especial ya que cambia la interpretacion de la var
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$')
		return (-1);
	return (0);
}

int	position_dolar(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
			return (++i);
		i++;
	}
	return (0);
}

char	*ft_strjoin_special(char *s1, char *s2, size_t i, size_t c) //funcion que concatena la $var y /aaa o lo que le manden despues de una $var siempre y cuando sea caracter especial
{
	char	*str;
	size_t	size1;

	size1 = ft_strlen(s1);
	if (s1[size1 - 1] == 34 || s1[size1 - 1] == 39)
		size1--;
	str = (char *)malloc(sizeof(char) * (size1 + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] && i < size1)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[c])
	{
		str[i + c] = s2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}
