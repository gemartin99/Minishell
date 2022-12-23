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
#include "../inc/libft/libft.h"

//funcion para checkear si hay un dolar en la linea que me mandan
//mirar esta funcion
int	check_dolar(char *line)
{
	int	i;
	int	doubles;

	i = 0;
	doubles = 1;
	while (line[i])
	{
		if (line[i] == 39 && doubles == 1)
			i = get_next_quote(i + 1, line, line[i]);
		if (line[i] == 34)
			doubles *= -1;
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

//linea 47 mirar leaks
char	*ft_replace_value2(char *s, int i)
{
	char	*res;
	char	*tmp;
	int		j;

	j = -1;
	res = malloc(sizeof(char) * ((ft_strlen(s) - 1) + ft_strlen
				(ft_itoa(g_error))));
	if (!res)
		exit_error("Error malloc", 55);
	tmp = ft_substr(s, 0, i);
	tmp = ft_strjoin(tmp, ft_itoa(g_error));
	j = -1;
	while (tmp[++j])
		res[j] = tmp[j];
	while (s[++i] && s[i + 1])
		res[j++] = s[i + 1];
	res[j] = '\0';
	return (res);
}

char	*ft_replace_value(char *s)
{
	int	i;
	int	j;

	i = get_next_quote(0, s, '$');
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
			s = ft_replace_value2(s, i);
		j = i;
		i = get_next_quote(0, s, '$');
		if (j == i)
			break ;
	}
	return (s);
}

//funcion strcmp modificada para variables de entorno
int	var_strcmp(char *s1, char *s2)
{
	size_t	i;

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

//funcion que concatena la $var y /aaa o lo que
//le manden despues de una $var siempre y cuando sea caracter especial
char	*ft_strjoin_special(char *s1, char *s2, size_t i, size_t c)
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
