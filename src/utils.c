/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 05:18:59 by smiro             #+#    #+#             */
/*   Updated: 2022/12/08 05:19:00 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_skip_space(char *s, int i)
{
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

t_cmd	*ft_last(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

char	*remove_quotes(char *str, char c) //Recive un string y le saca el caracter que resive
{
	int		i;
	char	*temp;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if (str[i] != c)
			size ++;
	}
	temp = malloc(sizeof(char) * size + 1);
	if (!temp)
		exit_error("Error malloc", 20);
	temp[size--] = '\0';
	while (--i >= 0)
	{
		if (str[i] != c)
		{
			temp[size] = str[i];
			size--;
		}
	}
	free(str);
	return (temp);
}

char	*str_tolower(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char	*str_noquotes(char *str) //Recive una string y devuelve una copia sin las comillas que no correspondan
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = 0;
	j = 0;
	doubles = 1;
	simples = 1;
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[i])
	{
		if (str[i] == 34 && simples != -1)
				doubles = -doubles;
		else if (str[i] == 39 && doubles != -1)
			simples = -simples;
		else
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	return (temp);
}
