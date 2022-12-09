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

int ft_skip_space(char *s, int i)
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

char	*remove_quotes(char *str, char c) //Recive un string y lo copia sin el caracter que resive
{
	int	i;
	char *temp;
	int	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != c)
			size ++;
		i++;
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
