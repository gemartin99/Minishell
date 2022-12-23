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
#include "../inc/libft/libft.h"

int	ft_skip_space(char *s, int i)
{
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

//Recive un string y le saca el caracter que resive
char	*remove_quotes(char *str, char c)
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
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

//Recive una string y devuelve una copia sin las comillas que no correspondan
char	*str_noquotes(char *str)
{
	int		i;
	int		j;
	char	*temp;
	int		doubles;
	int		simples;

	i = -1;
	j = -1;
	doubles = 1;
	simples = 1;
	temp = ft_calloc(1, ft_strlen(str) + 1);
	if (!temp)
		exit_error("Error malloc", 11);
	while (str[++i])
	{
		if (str[i] == 34 && simples != -1)
				doubles = -doubles;
		else if (str[i] == 39 && doubles != -1)
			simples = -simples;
		else
			temp[++j] = str[i];
	}
	return (temp);
}

int	check_nonpipables(t_cmd *cmd, char *temp_cmd)
{
	int	i;

	i = 0;
	if (cmd->next)
		i = 0;
	else if (!ft_strncmp(temp_cmd, "export", 7))
		i = 1;
	else if (!ft_strncmp(temp_cmd, "unset", 6))
		i = 1;
	else if (!ft_strncmp(temp_cmd, "exit", 5))
		i = 1;
	else if (!ft_strncmp(temp_cmd, "cd", 3))
		i = 1;
	free(temp_cmd);
	return (i);
}
